#include "asm.h"


int Assembler(Text* buf, Command* cmd, Label* Labels)
{
    assert(buf);
    assert(cmd);
        
    while (buf->nline < buf->nlines + 1)
    {
        int error_code = ParseInstruction(buf, cmd, Labels);
        buf->position ++;
        EmitInstrctionBinary(cmd, buf, Labels);

        cmd->code   = (char) MAX_IN_BYTE;
        cmd->value  =            INT_MAX;
        if (error_code != 0)
            return error_code; 
        buf->nline++;
    }
    return 0;
}

void OutputBinary(Text* buf, const char* output_file)
{
    assert(buf);
    assert(output_file);

    FILE* fname = fopen(output_file, "wb");
    assert(fname);

    fwrite(buf->binarycode, (size_t) buf->binary_position, sizeof(char), fname);
    
    fclose(fname);
}

int ParseInstruction(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);
    assert(Labels);

    sscanf(buf->buffer + buf->position, "%s", cmd->command_name);
    buf->position += strlen(cmd->command_name);

    return ParseOperand(buf, cmd, Labels);
}

int ParseOperand(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);
    assert(Labels);
    
    for (size_t counter = 0; counter < sizeof(cmds) / sizeof(*cmds); counter++)
    {
        if (strcmp(cmd->command_name, cmds[counter].name) == 0)
        {
            cmd->code = (char) (cmds[counter].valueName);

            if (cmds[counter].argument_type == STACK_ARGUMENTS)
                return  ParseValueArgument(buf, cmd);
            else if (cmds[counter].argument_type == LABEL_ARGUMENTS)
                return  ParseLabelArgument(buf, cmd, Labels);
            else
                return FindErrors(cmd);
        }
    }
    
    return ParseDefineLabel(buf, cmd, Labels);;
}
int ParseDefineLabel(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);
    
    buf->position = buf->position - strlen(cmd->command_name);

    if (cmd->command_name[strlen(cmd->command_name) - 1] == ':')
    {
        memcpy(cmd->argument, cmd->command_name, strlen(cmd->command_name) - 1);

        int result = CompareNameLabels(cmd->argument, Labels);
        if (result == -1)
        {
            memcpy(Labels[cmd->numberlabelcmd].name, cmd->argument, strlen(cmd->argument));
            Labels[cmd->numberlabelcmd].value_ptr = buf->binary_position; 

            cmd->numberlabelcmd++;
        }
        else
            Labels[result].value_ptr = buf->binary_position;
    }
    
    buf->position += strlen(cmd->command_name);

    return FindErrors(cmd);
}
int ParseLabelArgument(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);

    sscanf(buf->buffer + buf->position, "%s", cmd->argument);
    
    int result = CompareNameLabels(cmd->argument, Labels);
    
    if (result == -1)
    {
        memcpy(Labels[cmd->numberlabelcmd].name, cmd->argument, strlen(cmd->argument) + 1);
        cmd->value = result;
        cmd->numberlabelcmd++;
    }
    else
        cmd->value = Labels[result].value_ptr;

    buf->position += strlen(cmd->argument);
    buf->position += SPACE;
      
    return FindErrors(cmd);  
}

int ParseValueArgument(Text* buf, Command* cmd)
{
    assert(cmd);
    assert(buf);

    if (sscanf(buf->buffer + buf->position, "%d", &cmd->value) == 1)
    {
        cmd->code |= NUM_BIT;

        sscanf(buf->buffer + buf->position, "%s", cmd->argument);
        buf->position += strlen(cmd->argument);        
    }
    else
    {
        char string[MAX_SIZE_ARGUMENT] = {};

        sscanf(buf->buffer + buf->position, "%s", string);
        
        if ((string[0] == '[') && (sscanf(buf->buffer + buf->position + 2, "%d", &cmd->value) == 1))
        {
            cmd->code |= RAM_BIT;
            cmd->code |= NUM_BIT;

            sscanf(buf->buffer + buf->position + 2, "%s", cmd->argument);
            buf->position += strlen(cmd->argument) - 1;
            buf->position += 2 * sizeof(char);
        }
        else if (string[0] == '[')
        {
            cmd->code |= RAM_BIT;
            cmd->code |= REG_BIT;

            memcpy(cmd->reg, string + 1, 3 * sizeof(char));
            buf->position += strlen(cmd->reg);
            buf->position += 2 * sizeof(char);
        }
        else
        {
            cmd->code |= REG_BIT;

            memcpy(cmd->reg, string, strlen(string));
            buf->position += strlen(cmd->reg);
        }
    }

    buf->position += SPACE;
      
    return FindErrors(cmd);  
}

int WriteArrayRegister(Command* cmd)
{
    assert(cmd);

    for (size_t counter = 0; counter < sizeof(reg) / sizeof(char*); counter++)
        if (strcmp(cmd->reg, reg[counter]) == 0)
            return ((int)counter + 1);
    return 0;
}

int CompareNameLabels(char* string, Label* Labels)
{
    assert(string);
    assert(Labels);

    for (size_t counter = 0; counter < NUM_LABELS; counter++)
    {
        if (strcmp(string, Labels[counter].name) == 0)
            return (int)counter;   
    }
    return -1;
}

void EmitInstrctionBinary(Command* cmd, Text* buf, Label* Labels)
{
    assert(cmd);
    assert(buf);
    assert(Labels);

    if (cmd->code == (char) MAX_IN_BYTE)
        return;

    cmd->numberlabelcmd--;

    buf->binarycode[buf->binary_position] = cmd->code;

    if (cmd->code & NUM_BIT)
    {
        (buf->binary_position)++;
        memcpy(buf->binarycode + buf->binary_position, &cmd->value, sizeof(cmd->value));
        buf->binary_position += (int) sizeof(int);
    }
    else if (cmd->code & REG_BIT)
    {
        (buf->binary_position)++;
        buf->binarycode[buf->binary_position] = (char) WriteArrayRegister(cmd);
        (buf->binary_position)++;
    }
    else if (cmd->value != INT_MAX)
    {
        int offset = buf->binary_position - cmd->value;
        
        (buf->binary_position)++;
        memcpy(buf->binarycode + buf->binary_position, &offset, sizeof(int));
        buf->binary_position += (int) sizeof(int);
    }
    else
    {
        (buf->binary_position)++;
    }
    cmd->numberlabelcmd++;
}

int FindErrors(Command* cmd)
{
    int errors = 0;
    if (strlen(cmd->reg) > REF_SIZE_REGISTR)            errors = 1 << 0;
    if (strlen(cmd->command_name) > REF_SIZE_COMMAND)   errors = 1 << 1;
    if (strlen(cmd->argument) > REF_SIZE_ARGUMENT)      errors = 1 << 2;
    if (cmd->numberlabelcmd > NUM_LABELS - 1)           errors = 1 << 3;

    return errors;
}

int DumpErrors(int errors, Text* buf, Command* cmd)
{
    if (errors == 0)
        return 0;
    switch(errors) 
    {
        case 1 << 0:
            printf("ERRORS : WRONG REGISTER ENTERED AFTER THE COMMAND\n");
            printf("cmds.txt:%lu: %s%s\n", buf->nline + 1, cmd->command_name, cmd->reg);
            break;
        case 1 << 1:
            printf("ERRORS : WRONG COMMAND ENTERED\n");
            printf("cmds.txt:%lu: %s\n", buf->nline + 1, cmd->command_name);
            break;
        case 1 << 2:
            printf("ERRORS : WRONG ARGUMENT ENTERED AFTER THE COMMAND\n");
            printf("cmds.txt:%lu\n", buf->nline + 1);
            break;
        case 1 << 3:
            printf("ERRORS : LABEL COUNT IS HIGHER THAN NORMAL\n");
            printf("cmds.txt:%lu\n", buf->nline + 1);
            break;
        default:
            printf("EXTRA ERROR\n");
            break;
    }
    return errors;
}
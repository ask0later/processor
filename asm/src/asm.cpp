#include "asm.h"


int Assembler(Text* buf, Command* cmd, Label* Labels)
{
    assert(buf);
    assert(cmd);
        
    for (size_t numberline = 0; numberline < buf->num_lines; numberline++)
    {
        ReadLine(buf->start_line[numberline], cmd);
        ParseOperand(buf, cmd, Labels);

        EmitInstrctionBinary(cmd, buf, Labels);

        cmd->code   = (char) MAX_IN_BYTE;
        cmd->value  =            INT_MAX;

        
        memset(cmd->argument, 0, strlen(cmd->argument));
        memset(cmd->command_name, 0, strlen(cmd->command_name));
        buf->num_line++;
    }
    return 0;
}

void OutputBinary(Text* buf, const char* output_file)
{
    assert(buf);
    assert(output_file);

    FILE* fname = fopen(output_file, "wb");
    assert(fname);
    
    fwrite(buf->binary_code, (size_t) buf->binary_position, sizeof(char), fname);
    
    fclose(fname);
}

ProcessorError ReadLine(char* line, Command* cmd)
{
    if (*line == '\0')
        return ProcessorNO_ERROR;
        
    while (*line == ' ')
        line++;
        
    line = ReadWord(line, &cmd->command_name);

    while (*line == ' ')
        line++;

    line = ReadWord(line, &cmd->argument);

    return ProcessorNO_ERROR;
}

char* ReadWord(char* line, char** name)
{
    size_t i = 0;
    char temp[MAX_SIZE_ARGUMENT] = {};

    while((*line != ' ') && (*line != '\0'))
    {
        temp[i++] = *line;
        line++;
    }
    memcpy(*name, temp, i);

    return line;
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
            cmd->code = (char) (cmds[counter].value_name);

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

    size_t length = strlen(cmd->command_name);

    if (cmd->command_name[length - 1] == ':')
    {
        char label_name[MAX_SIZE_ARGUMENT] = {};

        memcpy(label_name, cmd->command_name, length - 1);

        int result = CompareNameLabels(label_name, Labels);
        if (result == -1)
        {
            memcpy(Labels[cmd->num_labels].name, cmd->argument, strlen(cmd->argument));
            Labels[cmd->num_labels].value_ptr = buf->binary_position;

            cmd->num_labels++;
        }
        else
            Labels[result].value_ptr = buf->binary_position;
    }
    //else
        //return function or label not found

    return FindErrors(cmd);
}
int ParseLabelArgument(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);

    int result = CompareNameLabels(cmd->argument, Labels);
    
    if (result == -1)
    {
        memcpy(Labels[cmd->num_labels].name, cmd->argument, strlen(cmd->argument) + 1);
        cmd->value = result;
        cmd->num_labels++;
    }
    else
        cmd->value = Labels[result].value_ptr;
      
    return FindErrors(cmd);  
}

int ParseValueArgument(Text* buf, Command* cmd)
{
    assert(cmd);
    assert(buf);

    if (sscanf(cmd->argument, "%d", &cmd->value) == 1)
    {
        cmd->code |= NUM_BIT;    
    }
    else
    {
        char string[MAX_SIZE_ARGUMENT] = {};

        sscanf(cmd->argument, "%s", string);
        size_t lenght = strlen(string);
        
        if ((string[0] == '[') && (sscanf(string + 1, "%d", &cmd->value) == 1))
        {
            cmd->code |= RAM_BIT;
            cmd->code |= NUM_BIT;
        }
        else if (string[0] == '[')
        {
            cmd->code |= RAM_BIT;
            cmd->code |= REG_BIT;

            memcpy(cmd->reg, string + 1, lenght - 2);
        }
        else
        {
            cmd->code |= REG_BIT;

            memcpy(cmd->reg, string, lenght);
        }
    }
      
    return FindErrors(cmd);  
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

    cmd->num_labels--;

    buf->binary_code[buf->binary_position] = cmd->code;

    if (cmd->code & NUM_BIT)
    {
        (buf->binary_position)++;
        memcpy(buf->binary_code + buf->binary_position, &cmd->value, sizeof(cmd->value));
        buf->binary_position += (int) sizeof(int);
    }
    else if (cmd->code & REG_BIT)
    {
        (buf->binary_position)++;
        buf->binary_code[buf->binary_position] = (char) (cmd->reg[1] - 'a' + (char)1);
        (buf->binary_position)++;
    }
    else if (cmd->value != INT_MAX)
    {
        int offset = buf->binary_position - cmd->value;
        
        (buf->binary_position)++;
        memcpy(buf->binary_code + buf->binary_position, &offset, sizeof(int));
        buf->binary_position += (int) sizeof(int);
    }
    else
    {
        (buf->binary_position)++;
    }
    cmd->num_labels++;
}

int FindErrors(Command* cmd)
{
    int errors = 0;
    if (strlen(cmd->reg) > REF_SIZE_REGISTR)            errors = 1 << 0;
    if (strlen(cmd->command_name) > REF_SIZE_COMMAND)   errors = 1 << 1;
    if (strlen(cmd->argument) > REF_SIZE_ARGUMENT)      errors = 1 << 2;
    if (cmd->num_labels > NUM_LABELS - 1)               errors = 1 << 3;

    return errors;
}

int DumpErrors(int errors, Text* buf, Command* cmd)
{
    if (errors == 0)
        return 0;
    switch(errors) 
    {
        case 1 << 0:
            printf("error : wrong register entered\n");
            printf("cmds.txt:%lu: %s%s\n", buf->num_line + 1, cmd->command_name, cmd->reg);
            break;
        case 1 << 1:
            printf("ERRORS : wrong coomand entered\n");
            printf("cmds.txt:%lu: %s\n", buf->num_line + 1, cmd->command_name);
            break;
        case 1 << 2:
            printf("ERRORS : WRONG ARGUMENT ENTERED AFTER THE COMMAND\n");
            printf("cmds.txt:%lu\n", buf->num_line + 1);
            break;
        case 1 << 3:
            printf("ERRORS : LABEL COUNT IS HIGHER THAN NORMAL\n");
            printf("cmds.txt:%lu\n", buf->num_line + 1);
            break;
        default:
            printf("EXTRA ERROR\n");
            break;
    }
    return errors;
}
#include "asm.h"


const char* BYTEcode       = "../BYTEcodefile.txt";
const char* bytecodebinary = "../bytebinarycode";


void Assembler(Text* buf, Command* cmd, Label* Labels)
{
    assert(buf);
    assert(cmd);

    char* ptr_line = buf->buffer;

    char* ptr = buf->binarycode;


    for (size_t counterptr = 0; counterptr < buf->nlines; counterptr++)
    {
        ptr_line = ParseInstruction(cmd, ptr_line, Labels, counterptr) + 1;
        EmitInstrction(cmd, Labels);
        EmitInstrctionBinary(cmd, buf, Labels);
        
        cmd->code   = (char) MAX_IN_BYTE;
        cmd->value  =      INT_MAX;
    }

    FILE* fname = fopen(bytecodebinary, "wb");

    fwrite(ptr, (size_t) (buf->binarycode - ptr + 1), sizeof(char),fname);

    free(ptr);
    fclose(fname);
}

char* ParseInstruction(Command* cmd, char* ptr_line, Label* Labels, size_t counterptr)
{
    assert(cmd);
    assert(ptr_line);

    sscanf(ptr_line, "%s", cmd->command_name);

    // strtok()
    char* position = ptr_line + strlen(cmd->command_name);

    return ParseOperand(cmd, position, Labels, counterptr);
}

char* ParseOperand(Command* cmd, char* position, Label* Labels, size_t counterptr)
{
    assert(cmd);
    assert(position);
    
    for (size_t counter = 0; counter < sizeof(cmds) / sizeof(*cmds); counter++)
    {
        if (strcmp(cmd->command_name, cmds[counter].name) == 0)
            {
                cmd->code = (char) (cmds[counter].valueName);
                
                if      (cmds[counter].argument_type == TWO_ARGUMENTS)
                    return  ParseValueArgument(cmd, position);
                else if (cmds[counter].argument_type == ONE_ARGUMENTS)
                    return ParseNumberArgument(cmd, position);
                else if (cmds[counter].argument_type == LABEL_ARGUMENTS)
                    return  ParseLabelArgument(cmd, position, Labels, counterptr);
                else
                    return position;
            }
    }
    return position;
}
char* ParseLabelArgument(Command* cmd, char* position, Label* Labels, size_t counterptr)
{
    assert(cmd);
    assert(position);

    cmd->code |= (char) LAB_BIT;

    char string[SIZE_ARGUMENT] = {};
    if (sscanf(position, "%d", &cmd->value) == 1)
    {
        cmd->code |= NUM_BIT;

        Labels[cmd->numberlabelcmd].value_ptr = (size_t) cmd->value;
        sscanf(position, "%s", string);
        
        position = position + strlen(string);        
    }
    else
    {
        sscanf(position, "%s", string);
        
        int result = CompareNameLabels(string, Labels);
        
        if (result == -1)
        {
            memcpy(Labels[cmd->numberlabelcmd].name, string, strlen(string) + 1);
            Labels[cmd->numberlabelcmd].value_ptr = (int) counterptr;
            cmd->numberlabelcmd++;
        }
        else
        {
            cmd->value = Labels[(size_t) result].value_ptr;
        }
        
        position = position + strlen(string);
    }
    position += SPACE;
      
    return position;  
}

char* ParseValueArgument(Command* cmd, char* position)
{
    assert(cmd);
    assert(position);
    
    if (sscanf(position, "%d", &cmd->value) == 1)
    {
        cmd->code |= NUM_BIT;

        char length[SIZE_ARGUMENT] = {};
        sscanf(position, "%s", length);
        
        position = position + strlen(length);        
    }
    else
    {
        cmd->code |= REG_BIT;

        sscanf(position, "%s", cmd->reg);

        position = position + strlen(cmd->reg);
    }
    position += SPACE;
      
    return position;  
}

char* ParseNumberArgument(Command* cmd, char* position)
{
    assert(cmd);
    assert(position);

    if (sscanf(position, "%s", cmd->reg) == 1)
    {
        cmd->code |= REG_BIT;

        sscanf(position, "%s", cmd->reg);
        
        position += strlen(cmd->reg);
        position += SPACE;
    }
    else 
    {
        cmd->code |= NUM_BIT;
    }
    return position;
}

void EmitInstrction(Command* cmd, Label* Labels)
{
    assert(cmd);
    
    FILE* fp = fopen(BYTEcode, "a");

    assert(fp);

    cmd->numberlabelcmd--;

    fprintf(fp, "%d", (unsigned char)cmd->code);


    if (cmd->code & NUM_BIT)
    {
        fprintf(fp," %d\n", cmd->value);
    }
    else if (cmd->code & REG_BIT)
    {
        fprintf(fp," %lu\n", WriteArrayRegister(cmd));            
    }
    else if (cmd->code & LAB_BIT)
    {
        if (cmd->value != INT_MAX)
            fprintf(fp, " %d\n", cmd->value);
        else
            fprintf(fp, " %d\n", (char)Labels[cmd->numberlabelcmd].value_ptr);
    }
    else
    {
        fprintf(fp, " \n");
    }
    cmd->numberlabelcmd++;
    fclose(fp);
}

size_t WriteArrayRegister(Command* cmd)
{
    assert(cmd);

    for (size_t counter = 0; counter < sizeof(reg) / sizeof(char*); counter++)
        if (strcmp(cmd->reg, reg[counter]) == 0)
            return (counter + 1);
    return 0;
}

int CompareNameLabels(char* string, Label* Labels)
{
    assert(string);
    assert(Labels);

    for (size_t counter = 0; counter < NUM_LABELS; counter++)
    {
        if (strcmp(string, Labels[counter].name) == 0)
            return (int) counter;   
    }
    return -1;
}

void EmitInstrctionBinary(Command* cmd, Text* buf, Label* Labels)
{
    *buf->binarycode = cmd->code;
    (buf->binarycode)++;

    if (cmd->code & NUM_BIT)
    {
        memcpy(buf->binarycode, &cmd->value, sizeof(cmd->value));
        buf->binarycode += sizeof(int);
    }
    else if (cmd->code & REG_BIT)
    {
        *buf->binarycode = (char) WriteArrayRegister(cmd);
        (buf->binarycode)++;
    }
    else if (cmd->code & LAB_BIT)
    {
        memcpy(buf->binarycode, &Labels[cmd->numberlabelcmd].value_ptr, sizeof(cmd->value));
        buf->binarycode += sizeof(int);
    }
}
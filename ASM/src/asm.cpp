#include "asm.h"


const char* BYTEcode = "../BYTEcodefile.txt";
const char* bytecodebinary = "../bytebinarycode";


void Assembler(Text* buf, Command* cmd)
{
    assert(buf);
    assert(cmd);

    char* ptr_line = buf->buffer;

    char* ptr = buf->binarycode;


    for (size_t counter = 0; counter < buf->nlines; counter++)
    {
        ptr_line = ParseInstruction(cmd, ptr_line) + 1;
        EmitInstrction(cmd);
        EmitInstrctionBinary(cmd, buf);
        
        cmd->code   = MAX_IN_BYTE;
        cmd->value  =     INT_MAX;
        cmd->reg[0] =     's';
    }

    //ptr = (char*) realloc(buf->binarycode, buf->memory_size);

    FILE* fname = fopen(bytecodebinary, "wb");

    fwrite(ptr, buf->binarycode - ptr + 1, sizeof(char),fname);

    free(ptr);
    fclose(fname);
}


char* ParseInstruction(Command* cmd, char* ptr_line)
{
    assert(cmd);
    assert(ptr_line);

    sscanf(ptr_line, "%s", cmd->command_name);

    // strtok()
    char* position = ptr_line + strlen(cmd->command_name);

    return ParseOperand(cmd, position);
}

char* ParseOperand(Command* cmd, char* position)
{
    assert(cmd);
    assert(position);
    
    for (size_t counter = 0; counter < sizeof(cmds) / sizeof(*cmds); counter++)
    {
        if (strcmp(cmd->command_name, cmds[counter].name) == 0)
            {
                cmd->code = (char) (cmds[counter].valueName);
                if      (cmds[counter].argument_type == TWO_ARGUMENTS)
                    return ParseValueArgument(cmd, position);
                else if (cmds[counter].argument_type == ONE_ARGUMENTS)
                    return ParseNumberArgument(cmd, position);
                else
                    return position;
            }
    }
    return position;
}

char* ParseValueArgument(Command* cmd, char* position)
{
    assert(cmd);
    assert(position);
    
    if (sscanf(position, "%d", &cmd->value) == 1)
    {
        cmd->code |= NUM_BIT;

        char length [10] = {};
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

void EmitInstrction(Command* cmd)
{
    assert(cmd);
    
    FILE* fp = fopen(BYTEcode, "a");

    assert(fp);

    fprintf(fp, "%d", cmd->code);
    
    
    if      (cmd->code & NUM_BIT)
    {
        fprintf(fp," %d\n", cmd->value);
    }
    else if (cmd->code & REG_BIT)
    {
        fprintf(fp," %lu\n", WriteArrayRegister(cmd));            
    }
    else
    {
        if (cmd->value != INT_MAX)
            fprintf(fp," %d\n", cmd->value);
        else
            fprintf(fp,   "\n");
    }
    fclose(fp);
}

size_t WriteArrayRegister(Command* cmd)
{

    for (size_t counter = 0; counter < sizeof(reg) / sizeof(char*); counter++)
        if (strcmp(cmd->reg, reg[counter]) == 0)
            return (counter + 1);
    return 0;
}

void EmitInstrctionBinary(Command* cmd, Text* buf)
{
    *buf->binarycode = cmd->code;
    (buf->binarycode)++;

    if (cmd->code & NUM_BIT)
    {
        memcpy(buf->binarycode, &cmd->value, sizeof(cmd->value));
        buf->binarycode += sizeof(int);
    }
    else if (cmd->code & REG_BIT)//
    {
        *buf->binarycode = (char) WriteArrayRegister(cmd);
        (buf->binarycode)++;
    }
}
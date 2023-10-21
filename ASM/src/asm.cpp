#include "asm.h"



const char* BYTEcode       = "../BYTEcodefile.txt";


void Assembler(Text* buf, Command* cmd, Label* Labels)
{
    assert(buf);
    assert(cmd);
    
    // char* ptr_line = buf->buffer;

    // char* ptr_binary = buf->binarycode;

    for (size_t counterptr = 0; counterptr < buf->nlines; counterptr++)
    {
        //printf("%d\n", counterptr);
        buf->position = ParseInstruction(buf, cmd, Labels) + 1;

        //PrintNumberCommands(cmd, Labels);
        EmitInstrctionBinary(cmd, buf, Labels);

        cmd->code   = (char) MAX_IN_BYTE;
        cmd->value  =            INT_MAX;
    }
    
}

void OutputBinary(Text* buf, const char* output_file)
{
    assert(buf);
    assert(output_file);

    //printf("size of binaryfile = %lu\n", buf->binary_position);
    FILE* fname = fopen(output_file, "wb");
    
    assert(fname);

    fwrite(buf->binarycode, (size_t) buf->binary_position, sizeof(char), fname);
    
    fclose(fname);
}

size_t ParseInstruction(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);
    assert(Labels);

    sscanf(buf->buffer + buf->position, "%s", cmd->command_name);
    // printf("POSITION %d\n", buf->position);
    // printf("что считалось = %s\n", cmd->command_name);
    //printf("+%lu\n", strlen(cmd->command_name));

    // strtok()
    //printf("символ = <%c> \n", buf->buffer[buf->position]);
    buf->position += strlen(cmd->command_name);
    //printf("символ = <%c> \n", buf->buffer[buf->position]);

    return ParseOperand(buf, cmd, Labels);
}

size_t ParseOperand(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);
    assert(Labels);
    
    for (size_t counter = 0; counter < sizeof(cmds) / sizeof(*cmds); counter++)
    {
        if (strcmp(cmd->command_name, cmds[counter].name) == 0)
        {
            cmd->code = (char) (cmds[counter].valueName);

            //printf("COMMAND = %d \n", cmd->code);
            // printf("name =  %s\n", cmd->command_name);
            
            if (cmds[counter].argument_type == TWO_ARGUMENTS)
                return  ParseValueArgument(buf, cmd);
            else if (cmds[counter].argument_type == ONE_ARGUMENTS)
                return ParseNumberArgument(buf, cmd);
            else if (cmds[counter].argument_type == LABEL_ARGUMENTS)
                return  ParseLabelArgument(buf, cmd, Labels);
            else
                return buf->position;
        }
    }
    return ParseDefineLabel(buf, cmd, Labels);
}
size_t ParseDefineLabel(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);
    
    //printf("до %d\n", buf->position);
    //printf("куда надо налево%lu\n",strlen(cmd->command_name));
    
    buf->position = buf->position - strlen(cmd->command_name);
    
    //printf("после %d\n", buf->position);
    
    char string[SIZE_ARGUMENT] = {};
    
    //sscanf(buf->buffer + buf->position, "%s", string);

    if (cmd->command_name[strlen(cmd->command_name) - 1] == ':')
    {
        memcpy(string, cmd->command_name, strlen(cmd->command_name) - 1);
        //printf("string <%s>\n", string);
        int result = CompareNameLabels(string, Labels);
        if (result == -1)
        {
            memcpy(Labels[cmd->numberlabelcmd].name, string, strlen(string)/*+1*/);
            Labels[cmd->numberlabelcmd].value_ptr = buf->binary_position; 
            //printf("Labels[%d].value_ptr = %d \n", cmd->numberlabelcmd, Labels[cmd->numberlabelcmd].value_ptr);
            cmd->numberlabelcmd++;
        }
        else
        {
            Labels[result].value_ptr = buf->binary_position;
            //printf("Labels[%d].value_ptr = %d \n", result, Labels[result].value_ptr);
        }
        
        // Labels[cmd->numberlabelcmd].value_ptr = (int) buf->binary_position; 
        // cmd->numberlabelcmd++;
    }
    
    buf->position += strlen(cmd->command_name);
    
    //buf->position += SPACE;
      
    return buf->position;
}
size_t ParseLabelArgument(Text* buf, Command* cmd, Label* Labels)
{
    assert(cmd);
    assert(buf);

    cmd->code |= (char) LAB_BIT;

    char string[SIZE_ARGUMENT] = {};

    sscanf(buf->buffer + buf->position, "%s", string);

    int result = CompareNameLabels(string, Labels);
    
    if (result == -1)
    {
        memcpy(Labels[cmd->numberlabelcmd].name, string, strlen(string) + 1);
        //printf("Labels[%d].name = %s \n", cmd->numberlabelcmd, Labels[cmd->numberlabelcmd].name);
        //Labels[cmd->numberlabelcmd].value_ptr = result; 
        cmd->value = result;
        cmd->numberlabelcmd++;
    }
    else
    {
        cmd->value = Labels[result].value_ptr;
    }

    buf->position += strlen(string);

    buf->position += SPACE;
      
    return buf->position;  
}

size_t ParseValueArgument(Text* buf, Command* cmd)
{
    assert(cmd);
    assert(buf);
    //printf("символ = <%c> \n", buf->buffer[buf->position]);
    sscanf(&buf->buffer[buf->position], "%d", &cmd->value);
    //printf("число = <%d>\n", cmd->value);

    if (sscanf(buf->buffer + buf->position, "%d", &cmd->value) == 1)
    {
        cmd->code |= NUM_BIT;

        char length[SIZE_ARGUMENT] = {};
        sscanf(buf->buffer + buf->position, "%s", length);
        //printf("+%lu\n", strlen(length));

        buf->position += strlen(length);        
    }
    else
    {
        cmd->code |= REG_BIT;

        sscanf(buf->buffer + buf->position, "%s", cmd->reg);

        buf->position += strlen(cmd->reg);
    }

    buf->position += SPACE;
      
    return buf->position;  
}

size_t ParseNumberArgument(Text* buf, Command* cmd)
{
    assert(cmd);
    assert(buf);

    if (sscanf(buf->buffer + buf->position, "%s", cmd->reg) == 1)
    {
        cmd->code |= REG_BIT;

        sscanf(buf->buffer + buf->position, "%s", cmd->reg);
        
        buf->position += strlen(cmd->reg);
        buf->position += SPACE;
    }
    else 
    {
        cmd->code |= NUM_BIT;
    }
    return buf->position;
}


void PrintNumberCommands(Command* cmd, Label* Labels)
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
            return (int)counter;   
    }
    return -1;
}

void EmitInstrctionBinary(Command* cmd, Text* buf, Label* Labels)
{
    assert(cmd);
    assert(buf);
    assert(Labels);

    //printf("COUNTER LABELS = %d\n", cmd->numberlabelcmd);

    if (cmd->code == (char) MAX_IN_BYTE)
        return;

    //printf("БЛЯТЬ СУКА НАХУЙ\n");
    cmd->numberlabelcmd--;
    //printf("COUNTER LABELS_____ = %d\n", cmd->numberlabelcmd);

    buf->binarycode[buf->binary_position] = cmd->code;
    (buf->binary_position)++;
        
    if (cmd->code & NUM_BIT)
    {
        memcpy(buf->binarycode + buf->binary_position, &cmd->value, sizeof(cmd->value));
        buf->binary_position += (int) sizeof(int);
    }
    else if (cmd->code & REG_BIT)
    {
        buf->binarycode[buf->binary_position] = (char) WriteArrayRegister(cmd);
        (buf->binary_position)++;
    }
    else if (cmd->code & LAB_BIT)
    {
        //printf("COUNTER LABELS = %d\n", cmd->numberlabelcmd);
        //printf("||%d|| ----- ||%d||\n", (int) buf->binary_position,cmd->value);// Labels[cmd->numberlabelcmd].value_ptr);


        int offset = buf->binary_position - cmd->value;  //Labels[cmd->numberlabelcmd].value_ptr; 
        //printf("||||%d||||\n", offset);
        memcpy(buf->binarycode + buf->binary_position, &offset, sizeof(int));
        buf->binary_position += (int) sizeof(int);
    }
    cmd->numberlabelcmd++;
}



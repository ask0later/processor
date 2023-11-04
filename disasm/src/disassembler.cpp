#include "disassembler.h"


int DisAssembler(Text* cmd, Label* Labels)
{
    FILE* fp = fopen("stack.txt", "a");

    while (cmd->position != cmd->sizebuf)
    {        
        FILE* fname = fopen("../disasm.txt", "a");
        DecodeCommand(cmd, fname, Labels);
        fclose(fname);
    }
    fclose(fp);

    return 0;
}

void DecodeCommand(Text* cmd, FILE* fname, Label* Labels)
{
    int argument = 0;
    char one_command = cmd->buffer[cmd->position];
    #define DEF_CMD(name, num, argumentType, code)                                                      \
        case num:                                                                                       \
        fprintf(fname, name);                                                                           \
        if      (argumentType == NO_ARGUMENTS)                                                          \
            fprintf(fname, "\n");                                                                       \
        else if (argumentType == STACK_ARGUMENTS)                                                       \
        {                                                                                               \
            fprintf(fname, " ");                                                                        \
            if (one_command & RAM_BIT)                                                                  \
            {                                                                                           \
                fprintf(fname, "[");                                                                    \
            }                                                                                           \
            if (one_command & NUM_BIT)                                                                  \
            {                                                                                           \
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));                \
                fprintf(fname, "%d", argument);                                                         \
                cmd->position += sizeof(int);                                                           \
            }                                                                                           \
            else if (one_command & REG_BIT)                                                             \
            {                                                                                           \
                memcpy(&argument, (cmd->buffer + cmd->position + 1), sizeof(char));                     \
                fprintf(fname, "%c", 'r');                                                              \
                fprintf(fname, "%c", 'a' + argument - 1);                                               \
                fprintf(fname, "%c", 'x');                                                              \
                cmd->position += sizeof(char);                                                          \
            }                                                                                           \
            if (one_command & RAM_BIT)                                                                  \
            {                                                                                           \
                fprintf(fname, "]");                                                                    \
            }                                                                                           \
            fprintf(fname, "\n");                                                                       \
        }                                                                                               \
        else if (argumentType == LABEL_ARGUMENTS)                                                       \
        {                                                                                               \
            memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));                    \
            cmd->position += sizeof(int);                                                               \
            fprintf(fname, " %d\n", argument);                                                          \
        }                                                                                               \
        cmd->position++;                                                                                \
        break;                                                                                          \

    switch((cmd->buffer[cmd->position]) & COMMAND_MASK)
    {
        #include "../../commands.h"
        default:
            cmd->position++;
            break;
    }

    #undef DEF_CMD
}
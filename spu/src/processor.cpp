#include "processor.h"


int Processor(Proc* spu, Text* cmd)
{
    FILE* fp = fopen("stack.txt", "a");

    while (cmd->position != cmd->sizebuf)
    {
        //printf(" position = %d |command = %d|\n", cmd->position, cmd->buffer[cmd->position]);
        if (cmd->buffer[cmd->position] == HTL)
            return 0;
        
        ExequteCommand(spu, cmd);
    }
    fclose(fp);

    return 0;
}

void ExequteCommand(Proc* spu, Text* cmd)
{
    int argument = 0, value1 = 0, value2 = 0, value3 = 0;
    
    #define DEF_CMD(name, num, argumentNum, code)            \
        case num:                                            \
        code                                                 \
        break;                                               \

    switch((cmd->buffer[cmd->position]) & COMMAND_MASK)
    {
        #include "../../commands.h"
        default:
            printf("ERROR");
            break;
    }

    #undef DEF_CMD
}
#include "processor.h"

int Processor(Stack* stk, Stack* adress, Text* cmd, int* RAM)
{
    FILE* fp = fopen("stack.txt", "a");

    while (cmd->position != cmd->sizebuf)
    {
        if (cmd->buffer[cmd->position] == HTL)
            return 0;
        
        ExequteCommand(stk, adress, cmd, RAM);
        
        PrintStackData(stk, fp);
    }
    fclose(fp);

    return 0;
}

void ExequteCommand(Stack* stk, Stack* adress, Text* cmd, int* RAM)
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
            cmd->position++;
            break;
    }

    #undef DEF_CMD
}


void OutputCyrcle(int* RAM)
{
    assert(RAM);

    for (size_t j = 0; j < 11; j++)
    {
        for (size_t i = 0; i < 11; i++)
        {
            printf("%d", RAM[11 * j + i]);
        }
    printf("\n");
    }
}
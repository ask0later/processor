#include "processor.h"


const char NUM_BIT = 16;
const char REG_BIT = 32;


int Processor(Stack* stk, Text* cmd)
{
    StackAction(stk, cmd);
    
    int errors = ErrorRate(stk);
    StackDump(stk, errors);
    return 0;
}


void StackAction(Stack* stk, Text* cmd)
{
    const char* buffer_end = cmd->buffer + cmd->sizebuf - 1;  

    while (cmd->buffer != buffer_end)
    {
        SwitchCommand(stk, cmd);
        int errors = ErrorRate(stk);
        StackDump(stk, errors);
    }
}

void SwitchCommand(Stack* stk, Text* cmd)
{
    int argument = 0, value1 = 0, value2 = 0;
    switch(*cmd->buffer)
    {
        case (NUM_BIT | PUSH):
            cmd->buffer++;
            memcpy(&argument, (int*)cmd->buffer, sizeof(int));
            cmd->buffer += 4;
            StackPush(argument, stk);

            break;
        case (REG_BIT | PUSH):
            cmd->buffer++;
            argument = stk->reg[(size_t) *(cmd->buffer) - 1];
            cmd->buffer++;

            StackPush(argument, stk);

            break;
        case (REG_BIT | POP):
            cmd->buffer++;
            argument = StackPop(stk);

            stk->reg[(size_t) *(cmd->buffer) - 1] = argument;

            break;
        case ADD:
            cmd->buffer++;
            StackPush(StackPop(stk) + StackPop(stk), stk);

            break;
        case SUB:
            cmd->buffer++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            StackPush(value2 - value1, stk);

            break;
        case MUL:
            cmd->buffer++;
            StackPush(StackPop(stk) * StackPop(stk), stk);

            break;
        case DIV:
            cmd->buffer++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            StackPush(value2 / value1, stk);

            break;
        case SQRT:
            cmd->buffer++;
            value1 = 100 * StackPop(stk);
            value1 =(int) sqrt((double) value1) / 10;
            StackPush(value1, stk);

            break;
        case SIN:
            cmd->buffer++;
            value1 = StackPop(stk);
            value1 = (int) sin((double) value1);
            StackPush(value1, stk);

            break;
        case COS:
            cmd->buffer++;
            value1 = StackPop(stk);
            value1 = (int) cos((double) value1);
            StackPush(value1, stk);

            break;
        case IN:
            cmd->buffer++;
            scanf("%d", &argument);
            StackPush(argument, stk);

            break;
        case OUT:
            cmd->buffer++;
            value1 = StackPop(stk);
            printf("||%d||\n", value1);

            break;
        case HTL:
            cmd->buffer++;
            
            return;
        default:
            cmd->buffer++;

            break;
    }
}
#include "processor.h"


int Processor(Stack* stk, Text* cmd)
{
    FILE* fp = fopen("stack.txt", "a");

    while (cmd->position != cmd->sizebuf - 1)
    {
        ExequteCommand(stk, cmd, cmd->buffer);
        
        PrintStackData(stk, fp);
    }
    fclose(fp);

    return 0;
}

void ExequteCommand(Stack* stk, Text* cmd, char* buffer_start)
{
    printf("position -- %d\n",  cmd->position);
    printf("command -- %d\n\n", cmd->buffer[cmd->position]);
    int argument = 0, value1 = 0, value2 = 0, value3 = 0;
    
    // cmd->buffer[cmd->position] & COMMAND_MASK
    switch(cmd->buffer[cmd->position])
    {
        // case PUSH:
        case (NUM_BIT | PUSH):
            cmd->position++;
            memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
            cmd->position += sizeof(int);
            StackPush(argument, stk);

            break;
        case (REG_BIT | PUSH):
            cmd->position++;
            argument = stk->reg[(size_t) cmd->buffer[cmd->position] - 1];
            cmd->position++;

            StackPush(argument, stk);

            break;
        case (REG_BIT | POP):
            cmd->position++;
            argument = StackPop(stk);

            stk->reg[(size_t) cmd->buffer[cmd->position] - 1] = argument;
            cmd->position++;

            break;
        case ADD:
            cmd->position++;
            StackPush(StackPop(stk) + StackPop(stk), stk);

            break;
        case SUB:
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            StackPush(value2 - value1, stk);

            break;
        case MUL:
            cmd->position++;
            StackPush(StackPop(stk) * StackPop(stk), stk);

            break;
        case DIV:
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            StackPush(value2 / value1, stk);

            break;
        case SQRT:
            cmd->position++;
            value1 = 100 * StackPop(stk);
            value1 =(int) sqrt((double) value1) / 10;
            StackPush(value1, stk);

            break;
        case SIN:
            cmd->position++;
            value1 = StackPop(stk);
            value1 = (int) sin((double) value1);
            StackPush(value1, stk);

            break;
        case COS:
            cmd->position++;
            value1 = StackPop(stk);
            value1 = (int) cos((double) value1);
            StackPush(value1, stk);

            break;
        case IN:
            cmd->position++;
            scanf("%d", &argument);
            StackPush(argument, stk);

            break;
        case (LAB_BIT | JA):
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 > value1)
                {
                    memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                    //cmd->position = cmd->position - argument;
                    value3 = (int) cmd->position;
                    cmd->position = (size_t)(value3 - argument);
                }
            else
                cmd->position += sizeof(int);

            break;
        case (LAB_BIT | JAE):
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 >= value1)
                {
                    memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                    value3 = (int) cmd->position;
                    cmd->position = (size_t)(value3 - argument);
                }
            else
                cmd->position += sizeof(int);

            break;
        case (LAB_BIT | JB):
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 < value1)
                {
                    memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                    value3 = (int) cmd->position;
                    cmd->position = (size_t)(value3 - argument);
                }
            else
                cmd->position += sizeof(int);

            break;
        case (LAB_BIT | JBE):
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 <= value1)
                {
                    memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                    value3 = (int) cmd->position;
                    cmd->position = (size_t)(value3 - argument);
                }
            else
                cmd->position += sizeof(int);
            
            break;
        case (LAB_BIT | JE):
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 == value1)
                {
                    memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                    value3 = (int) cmd->position;
                    cmd->position = (size_t)(value3 - argument);
                }
            else
                cmd->position += sizeof(int);
            
            break;
        case (LAB_BIT | JNE):
            cmd->position++;
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 != value1)
                {
                    memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                    value3 = (int) cmd->position;
                    cmd->position = (size_t)(value3 - argument);
                }
            else
                cmd->position += sizeof(int);
            
            break;
        case (LAB_BIT | JMP):
            cmd->position++;
            memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
            //cmd->position = cmd->position - argument;
            value3 = (int) cmd->position;
            cmd->position = (size_t)(value3 - argument);
            
            break;
        case (LAB_BIT | JM):
            
            break;
        case OUT:
            cmd->position++;
            value1 = StackPop(stk);
            printf("%d\n", value1);

            break;
        case HTL:
            cmd->position++;
            return;
        default:
            cmd->position++;
            break;
    }
}

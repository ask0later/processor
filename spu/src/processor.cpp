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

    switch((cmd->buffer[cmd->position]) & COMMAND_MASK)
    {
        case PUSH:
            cmd->position++;
            if (cmd->buffer[cmd->position - 1] & NUM_BIT)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
            }
            else if (cmd->buffer[cmd->position - 1] & REG_BIT)
            {
                argument = stk->reg[(size_t) cmd->buffer[cmd->position] - 1];    
            }
            if (cmd->buffer[cmd->position - 1] & RAM_BIT)
            {
                value1 = RAM[argument];
            }
            else
            {
                value1 = argument;
            }
            if (cmd->buffer[cmd->position - 1] & NUM_BIT)
                cmd->position += sizeof(int);
            else
                cmd->position += sizeof(char);

            StackPush(value1, stk);

            break;
        case POP:
            cmd->position++;
            value1 = StackPop(stk);
            

            if (cmd->buffer[cmd->position - 1] & NUM_BIT)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                cmd->position += sizeof(int);
                RAM[argument] = value1;
            }
            else if (cmd->buffer[cmd->position - 1] & RAM_BIT)
            {
                argument = stk->reg[(size_t) cmd->buffer[cmd->position] - 1];
                cmd->position += sizeof(char);
                RAM[argument] = value1;
            }
            else
            {
                stk->reg[(size_t) cmd->buffer[cmd->position] - 1] = value1;
                cmd->position += sizeof(char);
            }

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
        case JA:
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 > value1)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
                value3 = (int) cmd->position;
                cmd->position = (size_t)(value3 - argument);
            }
            else
                cmd->position += sizeof(int) + sizeof(char);

            break;
        case JAE:
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 >= value1)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
                value3 = (int) cmd->position;
                cmd->position = (size_t)(value3 - argument);
            }
            else
                cmd->position += sizeof(int) + sizeof(char);

            break;
        case JB:
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 < value1)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
                value3 = (int) cmd->position;
                cmd->position = (size_t)(value3 - argument);
            }
            else
                cmd->position += sizeof(int) + sizeof(char);

            break;
        case JBE:
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 <= value1)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
                value3 = (int) cmd->position;
                cmd->position = (size_t)(value3 - argument);
            }
            else
                cmd->position += sizeof(int) + sizeof(char);
            
            break;
        case JE:
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 == value1)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
                value3 = (int) cmd->position;
                cmd->position = (size_t)(value3 - argument);
            }
            else
                cmd->position += sizeof(int) + sizeof(char);
            
            break;
        case JNE:
            value1 = StackPop(stk);
            value2 = StackPop(stk);
            if (value2 != value1)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
                value3 = (int) cmd->position;
                cmd->position = (size_t)(value3 - argument);
            }
            else
                cmd->position += sizeof(int) + sizeof(char);
            
            break;
        case JMP:
            memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
            value3 = (int) cmd->position;
            cmd->position = (size_t)(value3 - argument);
            
            break;
        case JM:
            
            break;
        case CALL:
            memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
            value3 = (int) cmd->position;
            value1 = (int) (cmd->position + sizeof(char) + sizeof(int));
            
            StackPush(value1, adress);
            cmd->position = (size_t)(value3 - argument);
            break;
        
        case (RET):
            value1 = StackPop(adress);
            
            cmd->position = (size_t) value1;
            break;
        case OUT:
            cmd->position++;
            value1 = StackPop(stk);
            printf("|%2d|\n", value1);

            break;
        case HTL:

            return;
        default:
            cmd->position++;
            break;
    }
}

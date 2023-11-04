

#define DEF_LABEL_CMD(num, symbol)                                                           \
            value1 = StackPop(&(spu->stk));                                                  \
            value2 = StackPop(&(spu->stk));                                                  \
            if (value2 symbol value1)                                                        \
            {                                                                                \
                memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));     \
                value3 = (int) cmd->position;                                                \
                cmd->position = (size_t)(value3 - argument);                                 \
            }                                                                                \
            else                                                                             \
                cmd->position += sizeof(int) + sizeof(char);                                 \
                

#define ARIFMETIC_OPERATION(symbol)                                                          \
            value1 = StackPop(&(spu->stk));                                                  \
            value2 = StackPop(&(spu->stk));                                                  \
            StackPush(value2 symbol value1, &(spu->stk));                                    \



DEF_CMD("push", PUSH, STACK_ARGUMENTS,
{
            cmd->position++;
            if (cmd->buffer[cmd->position - 1] & NUM_BIT)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
            }
            else if (cmd->buffer[cmd->position - 1] & REG_BIT)
            {
                argument = spu->reg[(size_t) cmd->buffer[cmd->position] - 1];    
            }
            if (cmd->buffer[cmd->position - 1] & RAM_BIT)
            {
                value1 = spu->RAM[argument];
            }
            else
            {
                value1 = argument;
            }
            if (cmd->buffer[cmd->position - 1] & NUM_BIT)
                cmd->position += sizeof(int);
            else
                cmd->position += sizeof(char);

            StackPush(value1, &(spu->stk));
}
)

DEF_CMD("pop", POP, STACK_ARGUMENTS,
{
            cmd->position++;
            value1 = StackPop(&(spu->stk));
        
            if (cmd->buffer[cmd->position - 1] & NUM_BIT)
            {
                memcpy(&argument, (int*)(cmd->buffer + cmd->position), sizeof(int));
                cmd->position += sizeof(int);
                spu->RAM[argument] = value1;
            }
            else if (cmd->buffer[cmd->position - 1] & RAM_BIT)
            {
                argument = spu->reg[(size_t) cmd->buffer[cmd->position] - 1];
                cmd->position += sizeof(char);
                
                spu->RAM[argument] = value1;
            }
            else
            {
                spu->reg[(size_t) cmd->buffer[cmd->position] - 1] = value1;
                cmd->position += sizeof(char);
            }
}
)

DEF_CMD("add", ADD, NO_ARGUMENTS,
{         
            cmd->position++;
            ARIFMETIC_OPERATION(+)
}
)

DEF_CMD("sub", SUB, NO_ARGUMENTS,
{
            cmd->position++;
            ARIFMETIC_OPERATION(-)
}
)

DEF_CMD("mul", MUL, NO_ARGUMENTS,
{
            cmd->position++;
            ARIFMETIC_OPERATION(*)
}
)


DEF_CMD("div", DIV, NO_ARGUMENTS,
{
            cmd->position++;
            ARIFMETIC_OPERATION(/)
}
)


DEF_CMD("sqrt", SQRT, NO_ARGUMENTS,
{
            cmd->position++;
            value1 = 100 * StackPop(&(spu->stk));
            value1 =(int) sqrt((double) value1) / 10;
            StackPush(value1, &(spu->stk));
}
)

DEF_CMD("sin", SIN, NO_ARGUMENTS,
{
            cmd->position++;
            value1 = StackPop(&(spu->stk));
            value1 = (int) sin((double) value1);
            StackPush(value1, &(spu->stk));
}
)


DEF_CMD("cos", COS, NO_ARGUMENTS, 
{
            cmd->position++;
            value1 = StackPop(&(spu->stk));
            value1 = (int) cos((double) value1);
            StackPush(value1, &(spu->stk));
}
)

DEF_CMD("in", IN, NO_ARGUMENTS, 
{
            cmd->position++;
            scanf("%d", &argument);
            StackPush(argument, &(spu->stk));
}
)

DEF_CMD("ja",  JA,  LABEL_ARGUMENTS,  {DEF_LABEL_CMD(JA,  > )})

DEF_CMD("jae", JAE, LABEL_ARGUMENTS,  {DEF_LABEL_CMD(JAE, >=)})

DEF_CMD("jb",  JB,  LABEL_ARGUMENTS,  {DEF_LABEL_CMD(JB,  < )}) 
        
DEF_CMD("jbe", JBE, LABEL_ARGUMENTS,  {DEF_LABEL_CMD(JBE, <=)})

DEF_CMD("jbe", JE,  LABEL_ARGUMENTS,  {DEF_LABEL_CMD(JE,  ==)})

DEF_CMD("jne", JNE, LABEL_ARGUMENTS,  {DEF_LABEL_CMD(JNE, > )})

DEF_CMD("jmp", JMP, LABEL_ARGUMENTS,
{
            memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
            value3 = (int) cmd->position;
            cmd->position = (size_t)(value3 - argument);
}
)

DEF_CMD("jm",   JM,   LABEL_ARGUMENTS, {})

DEF_CMD("call", CALL, LABEL_ARGUMENTS,
{
            memcpy(&argument, (int*)(cmd->buffer + cmd->position + 1), sizeof(int));
            value3 = (int)  cmd->position;
            value1 = (int) (cmd->position + sizeof(char) + sizeof(int));
            
            StackPush(value1, &(spu->adress));
            cmd->position = (size_t)(value3 - argument);
}
)

DEF_CMD("ret", RET, NO_ARGUMENTS,
{
            value1 = StackPop(&(spu->adress));
            cmd->position = (size_t) value1;
}
)

DEF_CMD("out", OUT, NO_ARGUMENTS,
{
            cmd->position++;
            value1 = StackPop(&(spu->stk));
            printf("|%2d|\n", value1);
}
)

DEF_CMD("htl", HTL, NO_ARGUMENTS,
{ 
            return;
}
)

DEF_CMD("draw", DRAW, NO_ARGUMENTS,
{
            cmd->position++;
            for(size_t i = 0; i < SQUARE_SIDE; i++)
            {
                for(size_t j = 0; j < SQUARE_SIDE; j++)
                {
                    printf("%2d", spu->RAM[ i * SQUARE_SIDE + j ]);
                }
                printf("\n");
            }
}
)
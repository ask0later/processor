#include "readCmd.h"
#include "stack.h"
#include "processor.h"

int main()
{
    struct Text  cmd    = {};
    struct Stack stk    = {};
    struct Stack adress = {};

    

    CreateBuffer(&cmd);
    StackCtor(&stk);
    StackCtor(&adress);

    Processor(&stk, &adress, &cmd);

    StackDtor(&adress);
    StackDtor(&stk);
    DeleteBuffer(&cmd);
}
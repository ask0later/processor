#include "readCmd.h"
#include "stack.h"
#include "processor.h"

int main()
{
    struct Text  cmd = {};
    struct Stack stk = {};

    CreateBuffer(&cmd);
    StackCtor(&stk);

    Processor(&stk, &cmd);

    StackDtor(&stk);
    DeleteBuffer(&cmd);
}
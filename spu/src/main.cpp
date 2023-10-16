#include "readCmd.h"
#include "stack.h"
#include "processor.h"

int main()
{
    struct Text  buf = {};
    struct Stack stk = {};

    CreateBuffer(&buf);
    StackCtor(&stk);
    //printf("%lu start \n", buf.buffer);

    Processor(&stk, &buf);

    StackDtor(&stk);
    DeleteBuffer(&buf);
}
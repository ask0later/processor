#include "readCmd.h"
#include "stack.h"
#include "processor.h"

int main()
{
    struct Text  cmd    = {};
    struct Stack stk    = {};
    struct Stack adress = {};
    
    int RAM[SIZE_RAM]   = {};
    CreateBuffer(&cmd);
    StackCtor(&stk);
    StackCtor(&adress);
    
    Processor(&stk, &adress, &cmd, RAM);

    OutputCyrcle(RAM);

    StackDtor(&adress);
    StackDtor(&stk);
    DeleteBuffer(&cmd);
}
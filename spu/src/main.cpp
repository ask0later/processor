#include "readCmd.h"
#include "stack.h"
#include "processor.h"

int main()
{
    struct Text  cmd    = {};
    struct Stack stk    = {};
    struct Stack adress = {};
    
    int RAM[SIZE_RAM]   = {};
    printf("БЛЯТЬ\n");
    CreateBuffer(&cmd);
    StackCtor(&stk);
    StackCtor(&adress);
    printf("БЛЯТЬ\n");
    Processor(&stk, &adress, &cmd, RAM);
    printf("RAM[0] = %d\n", RAM[0]);
    printf("RAM[1] = %d\n", RAM[1]);
    printf("RAM[2] = %d\n", RAM[2]);
    printf("RAM[3] = %d\n", RAM[3]);
    printf("RAM[4] = %d\n", RAM[4]);
    printf("RAM[5] = %d\n", RAM[5]);
    printf("RAM[6] = %d\n", RAM[6]);
    printf("RAM[7] = %d\n", RAM[7]);
    printf("RAM[8] = %d\n", RAM[8]);
    printf("RAM[9] = %d\n", RAM[9]);
    printf("RAM[10] = %d\n", RAM[10]);
    printf("RAM[11] = %d\n", RAM[11]);
    printf("RAM[12] = %d\n", RAM[12]);
    printf("RAM[13] = %d\n", RAM[13]);
    printf("RAM[14] = %d\n", RAM[14]);
    printf("RAM[15] = %d\n", RAM[15]);
    printf("RAM[16] = %d\n", RAM[16]);
    printf("БЛЯТЬ\n");
    StackDtor(&adress);
    StackDtor(&stk);
    DeleteBuffer(&cmd);
}
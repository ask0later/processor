#ifndef PROCESSORlib
#define PROCESSOR
#include <math.h>
#include <stdio.h>
#include <cstring>
#include "stack.h"
#include "../../enum.h" 
#include "readCmd.h"


const size_t SIZE_RAM = 121;
const int MAX_SIZE_COMMAND = 0b00001111;

const unsigned char COMMAND_MASK =  0b00011111;

const unsigned char NUM_BIT      =  1 << 5;
const unsigned char REG_BIT      =  1 << 6;
const unsigned char RAM_BIT      =  1 << 7;

const int     DEFINE_LABEL = 4;
const int  LABEL_ARGUMENTS = 3;
const int  STACK_ARGUMENTS = 2;
const int     NO_ARGUMENTS = 0;
    // 

const int valuecmd[] = {PUSH, POP, ADD, SUB, MUL, DIV, SQRT, SIN, COS, IN, JA, JAE, JB, JBE, JE, JNE, JMP, JM, CALL, RET, OUT, HTL};

int Processor(Stack* stk, Stack* adress, Text* cmd, int* RAM);
void   OutputCyrcle(int* RAM);

void ExequteCommand(Stack* stk, Stack* adress, Text* cmd, int* RAM);

#endif
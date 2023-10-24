#ifndef PROCESSORlib
#define PROCESSOR
#include <math.h>
#include <stdio.h>
#include <cstring>
#include "stack.h"
#include "../../commands.h" 
#include "readCmd.h"


const size_t SIZE_RAM = 100;
const int MAX_SIZE_COMMAND = 15;

const unsigned char COMMAND_MASK =  31;

const unsigned char NUM_BIT      =  32;
const unsigned char REG_BIT      =  64;
const char          RAM_BIT      = 128;


const int valuecmd[] = {PUSH, POP, ADD, SUB, MUL, DIV, SQRT, SIN, COS, IN, JA, JAE, JB, JBE, JE, JNE, JMP, JM, CALL, RET, OUT, HTL};

int Processor(Stack* stk, Stack* adress, Text* cmd, int* RAM);
void   OutputCyrcle(int* RAM);

void ExequteCommand(Stack* stk, Stack* adress, Text* cmd, int* RAM);

#endif
#ifndef PROCESSORlib
#define PROCESSOR
#include <math.h>
#include <stdio.h>
#include <cstring>
#include "stack.h"
#include "../../commands.h" 
#include "readCmd.h"

int const MAX_SIZE_COMMAND = 15;

const unsigned char NUM_BIT = 32;
const unsigned char REG_BIT = 64;
const char LAB_BIT = 128;

const int valuecmd[] = {PUSH, POP, ADD, SUB, MUL, DIV, SQRT, SIN, COS, IN, JA, JAE, JB, JBE, JE, JNE, JMP, JM, OUT, HTL};

int    Processor(Stack* stk, Text* cmd);

void ExequteCommand(Stack* stk, Text* cmd, char* buffer_start); 

#endif
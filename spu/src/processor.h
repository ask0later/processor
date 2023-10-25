#ifndef PROCESSORlib
#define PROCESSOR
#include <math.h>
#include <stdio.h>
#include <cstring>
#include "stack.h"
#include "../../enum.h" 
#include "readCmd.h"


const size_t SIZE_RAM = 121;
const int       MAX_SIZE_COMMAND = 0b00001111;
const unsigned char COMMAND_MASK = 0b00011111;

const int valuecmd[] = {PUSH, POP, ADD, SUB, MUL, DIV, SQRT, SIN, COS, IN, JA, JAE, JB, JBE, JE, JNE, JMP, JM, CALL, RET, OUT, HTL};

int       Processor(Stack* stk, Stack* adress, Text* cmd, int* RAM);
void ExequteCommand(Stack* stk, Stack* adress, Text* cmd, int* RAM);
void   OutputCyrcle(                                      int* RAM);
#endif
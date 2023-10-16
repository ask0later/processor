#ifndef PROCESSORlib
#define PROCESSOR
#include <math.h>
#include <stdio.h>
#include <cstring>
#include "stack.h"
#include "../../commands.h" 
#include "readCmd.h"

int const MAX_SIZE_COMMAND = 15;

const int valuecmd[] = {PUSH, POP, ADD, SUB, MUL, DIV, SQRT, SIN, COS, IN, OUT, HTL};

int    Processor(Stack* stk, Text* buf);


void   StackAction(Stack* stk, Text* buf);
void SwitchCommand(Stack* stk, Text* cmd); 

#endif
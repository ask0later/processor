#ifndef PROCESSORlib
#define PROCESSOR
#include <math.h>
#include <stdio.h>
#include <cstring>
#include "stack.h"
#include "../../enum.h" 
#include "readCmd.h"

const size_t    SIZE_RAM = 121;
const size_t    SQUARE_SIDE = 11;
const int       MAX_SIZE_COMMAND = 0b00001111;
const unsigned char COMMAND_MASK = 0b00011111;

struct Proc 
{
    int reg[NUM_REG];
    int RAM[SIZE_RAM] = {};
    Stack stk;
    Stack adress;
};

int       Processor(Proc* spu, Text* cmd);
void ExequteCommand(Proc* spu, Text* cmd);

#endif
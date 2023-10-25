#ifndef COMMANDS
#define COMMANDS

const unsigned char NUM_BIT      =  1 << 5;
const unsigned char REG_BIT      =  1 << 6;
const unsigned char RAM_BIT      =  1 << 7;

const int     DEFINE_LABEL = 4;
const int  LABEL_ARGUMENTS = 3;
const int  STACK_ARGUMENTS = 2;
const int     NO_ARGUMENTS = 0;

enum Commands
{   
    PUSH =  1, POP  =  2,
    ADD  =  3, SUB  =  4,
    MUL  =  5, DIV  =  6, 
    SQRT =  7,
    SIN  =  8, COS  =  9,
    IN   = 10,
    JA   = 11, JAE  = 12, JB   = 13,
    JBE  = 14, JE   = 15, JNE  = 16,
    JMP  = 17, JM   = 18,
    CALL = 19, RET  = 20, 
    OUT  = 21, HTL  = 22
};

#endif
#ifndef ASSEMBLER
#define ASSEMBLER

#include <math.h>

#include "readFile.h"
#include "../../commands.h"

const int TWO_ARGUMENTS = 2;
const int ONE_ARGUMENTS = 1;
const int  NO_ARGUMENTS = 0;

//const char MAX_IN_BYTE    = 255;




//const char* const commands[] = {push, pop, add, sub, mul, div_, sqrt, sin, cos, in, out, htl};
const struct NameAndType cmds[] = {{"push", TWO_ARGUMENTS, PUSH}, {"pop", ONE_ARGUMENTS, POP}, {"add", NO_ARGUMENTS,  ADD},\
                                    {"sub" , NO_ARGUMENTS,   SUB}, {"mul", NO_ARGUMENTS,  MUL}, {"div", NO_ARGUMENTS,  DIV},\
                                    {"sqrt", NO_ARGUMENTS,  SQRT}, {"sin", NO_ARGUMENTS,  SIN}, {"cos", NO_ARGUMENTS,  COS},\
                                    {"in",   NO_ARGUMENTS,    IN}, {"out", NO_ARGUMENTS,  OUT}, {"htl", NO_ARGUMENTS,  HTL}};

const char* const     reg[] = {"rax", "rbx", "rcx"};

const char RAX = 1;
const char RBX = 2;
const char RCX = 3;

const size_t SPACE = 1;

const char NUM_BIT = 16;
const char REG_BIT = 32;

const char BIT = 2;
const size_t SIZEBYTE = 8;


void         Assembler(Text* buf, Command* cmd);

char* ParseInstruction(Command* cmd, char* ptr_line);
void    EmitInstrction(Command* cmd);

char*             ParseOperand(Command* cmd, char* position);
char*      ParseNumberArgument(Command* cmd, char* position);
char*       ParseValueArgument(Command* cmd, char* position);

size_t      WriteArrayRegister(Command* cmd);


void EmitInstrctionBinary(Command* cmd, Text* buf);
void FromIntTo4char(Command* cmd, Text* buf);




#endif
#ifndef ASSEMBLER
#define ASSEMBLER

#include <math.h>

#include "readFile.h"
#include "../../commands.h"
const int     DEFINE_LABEL = 4;
const int  LABEL_ARGUMENTS = 3;
const int    TWO_ARGUMENTS = 2;
const int    ONE_ARGUMENTS = 1;
const int     NO_ARGUMENTS = 0;






//const char* const commands[] = {push, pop, add, sub, mul, div_, sqrt, sin, cos, in, out, htl};
const struct OneCommand cmds[] = {{"push",  TWO_ARGUMENTS,   PUSH}, {"pop", ONE_ARGUMENTS,   POP}, {"add", NO_ARGUMENTS,    ADD},
                                   {"sub" , NO_ARGUMENTS,     SUB}, {"mul", NO_ARGUMENTS,    MUL}, {"div", NO_ARGUMENTS,    DIV},
                                   {"sqrt", NO_ARGUMENTS,    SQRT}, {"sin", NO_ARGUMENTS,    SIN}, {"cos", NO_ARGUMENTS,    COS},
                                   {"in",   NO_ARGUMENTS,      IN}, {"ja",  LABEL_ARGUMENTS,  JA}, {"jae", LABEL_ARGUMENTS, JAE}, 
                                   {"jb",   LABEL_ARGUMENTS,   JB}, {"jbe", LABEL_ARGUMENTS, JBE}, {"je",  LABEL_ARGUMENTS,  JE},
                                   {"jne",  LABEL_ARGUMENTS,  JNE}, {"jmp", LABEL_ARGUMENTS, JMP}, {"jm",  LABEL_ARGUMENTS,  JM}, 
                                   {"out",  NO_ARGUMENTS,     OUT}, {"htl", NO_ARGUMENTS,    HTL}};

const char* const         reg[] = {"rax", "rbx", "rcx"};

const char RAX = 1;
const char RBX = 2;
const char RCX = 3;

const size_t SPACE = 1;

const unsigned char NUM_BIT =  32;
const unsigned char REG_BIT =  64;
const unsigned char LAB_BIT = 128;






const char BIT = 2;
const size_t SIZEBYTE = 8;


void                 Assembler(Text* buf, Command* cmd, Label* Labels);

size_t                    ParseInstruction(Text* buf, Command* cmd, Label* Labels); //cringe  
size_t                        ParseOperand(Text* buf, Command* cmd, Label* Labels);
size_t                 ParseNumberArgument(Text* buf, Command* cmd);
size_t                  ParseValueArgument(Text* buf, Command* cmd);
size_t                  ParseLabelArgument(Text* buf, Command* cmd, Label* Labels);
size_t                    ParseDefineLabel(Text* buf, Command* cmd, Label* Labels);

size_t      WriteArrayRegister(Command* cmd);
int          CompareNameLabels(char* string, Label* Labels);

void EmitInstrctionBinary(Command* cmd, Text* buf, Label* Labels);
void  PrintNumberCommands(Command* cmd,            Label* Labels);

void         OutputBinary(Text* buf, const char* output_file);




#endif
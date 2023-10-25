#ifndef ASSEMBLER
#define ASSEMBLER

#include <math.h>

#include "readFile.h"
#include "../../enum.h"

const struct OneCommand cmds[] = {{"push", STACK_ARGUMENTS, PUSH}, {"pop", STACK_ARGUMENTS,  POP}, {"add", NO_ARGUMENTS,    ADD},
                                  {"sub" , NO_ARGUMENTS,     SUB}, {"mul", NO_ARGUMENTS,     MUL}, {"div", NO_ARGUMENTS,    DIV},
                                  {"sqrt", NO_ARGUMENTS,    SQRT}, {"sin", NO_ARGUMENTS,     SIN}, {"cos", NO_ARGUMENTS,    COS},
                                  {"in",   NO_ARGUMENTS,      IN}, {"ja",  LABEL_ARGUMENTS,   JA}, {"jae", LABEL_ARGUMENTS, JAE}, 
                                  {"jb",   LABEL_ARGUMENTS,   JB}, {"jbe", LABEL_ARGUMENTS,  JBE}, {"je",  LABEL_ARGUMENTS,  JE},
                                  {"jne",  LABEL_ARGUMENTS,  JNE}, {"jmp", LABEL_ARGUMENTS,  JMP}, {"jm",  LABEL_ARGUMENTS,  JM},
                                  {"call", LABEL_ARGUMENTS, CALL}, {"ret", NO_ARGUMENTS,     RET}, 
                                  {"out",  NO_ARGUMENTS,     OUT}, {"htl", NO_ARGUMENTS,     HTL}};

const char* const         reg[] = {"rax", "rbx", "rcx"};

const char RAX = 1;
const char RBX = 2;
const char RCX = 3;

const size_t SPACE = 1;


const char   BIT      = 2;
const size_t SIZEBYTE = 8;


void                 Assembler(Text* buf, Command* cmd, Label* Labels);

size_t        ParseInstruction(Text* buf, Command* cmd, Label* Labels);  
size_t            ParseOperand(Text* buf, Command* cmd, Label* Labels);
size_t     ParseNumberArgument(Text* buf, Command* cmd               );
size_t      ParseValueArgument(Text* buf, Command* cmd               );
size_t      ParseLabelArgument(Text* buf, Command* cmd, Label* Labels);
size_t        ParseDefineLabel(Text* buf, Command* cmd, Label* Labels);

size_t      WriteArrayRegister(Command* cmd                          );
void      EmitInstrctionBinary(Command* cmd, Text* buf, Label* Labels);
void       PrintNumberCommands(Command* cmd,            Label* Labels);
int          CompareNameLabels(char* string,            Label* Labels);

void              OutputBinary(Text* buf, const char* output_file     );




#endif
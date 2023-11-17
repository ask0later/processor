#ifndef ASSEMBLER
#define ASSEMBLER

#include <math.h>

#include "readFile.h"
#include "../../enum.h"


#define DEF_CMD(name, num, argumentNum, code)                         \
                {name, argumentNum, num},                             \
                                                                      \

const struct OneCommand cmds[] = {
    #include "../../commands.h"
    {"null", NO_ARGUMENTS, 999}
};


const char RAX = 1;
const char RBX = 2;
const char RCX = 3;

const size_t SPACE = 1;


const char   BIT      = 2;
const size_t SIZEBYTE = 8;
const size_t SIZE_REG = 3;


int                  Assembler(Text* buf, Command* cmd, Label* Labels);

int           ParseInstruction(Text* buf, Command* cmd, Label* Labels);  
int               ParseOperand(Text* buf, Command* cmd, Label* Labels);
int         ParseValueArgument(Text* buf, Command* cmd               );
int         ParseLabelArgument(Text* buf, Command* cmd, Label* Labels);
int           ParseDefineLabel(Text* buf, Command* cmd, Label* Labels);

ProcessorError ReadLine(char* line, Command* cmd);
char* ReadWord(char* line, char** name);

void      EmitInstrctionBinary(Command* cmd, Text* buf, Label* Labels);
int          CompareNameLabels(char* string,            Label* Labels);
void              OutputBinary(Text* buf, const char* output_file     );

int DumpErrors(int errors, Text* buf, Command* cmd);
int FindErrors(                       Command* cmd);




#endif
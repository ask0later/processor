#ifndef DISASSEMBLER
#define DISASSEMBLER
#include "readCmd.h"
#include "../../enum.h"




const int MAX_SIZE_COMMAND = 15;
const size_t NUM_LABELS = 10;
struct Label
{
    char name[MAX_SIZE_COMMAND];
    int                value_ptr;
};

const unsigned char COMMAND_MASK = 0b00011111;

int    DisAssembler(Text* cmd, Label* Labels);
void  DecodeCommand(Text* cmd, FILE* fname, Label* Labels);

int   CompareNameLabels(char* string, Label* Labels);



#endif
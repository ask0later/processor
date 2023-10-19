#include "readFile.h"
#include "asm.h"

// arg[1] - input_file
int main()
{
    struct Text    buf = {};
    struct Command cmd = {};
    

    struct Label Labels[NUM_LABELS] = {{"POISON", -1,}, {"POISON", -1,}, {"POISON", -1,},
                                       {"POISON", -1,}, {"POISON", -1,}, {"POISON", -1,}, 
                                       {"POISON", -1,}, {"POISON", -1,}, {"POISON", -1,}, {"POISON", -1,}};
    
    CreateBuffer(&buf, &cmd);

    Assembler(&buf, &cmd, Labels);
    
    DeleteBuffer(&buf, &cmd);
}
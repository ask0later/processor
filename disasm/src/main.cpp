#include "readCmd.h"
#include "disassembler.h"

int main(const int argc, const char* argv[])
{
    if (argc == 2)
    {
        struct Text cmd = {};
        struct Label Labels[NUM_LABELS] = {{"LABEL_1", -1,}, {"LABEL_2", -1,}, {"LABEL_3", -1,},
                                           {"LABEL_4", -1,}, {"LABEL_5", -1,}, {"LABEL_6", -1,}, 
                                           {"LABEL_7", -1,}, {"LABEL_8", -1,}, {"LABEL_9", -1,}, {"LABEL_10", -1,}}; 
        CreateBuffer(&cmd);
    
        DisAssembler(&cmd, Labels);
    
        DeleteBuffer(&cmd);
        return 0;
    }
    printf("error: insufficient number of command line arguments\n");
    
    return 1;
}
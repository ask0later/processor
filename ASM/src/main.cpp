#include "readFile.h"
#include "asm.h"


int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        const char*  input_file = argv[1];
        const char* output_file = argv[2];

        struct Text    buf = {};
        struct Command cmd = {};
    

        struct Label Labels[NUM_LABELS] = {{"XXX", -1,}, {"XXX", -1,}, {"XXX", -1,},
                                           {"XXX", -1,}, {"XXX", -1,}, {"XXX", -1,}, 
                                           {"XXX", -1,}, {"XXX", -1,}, {"XXX", -1,}, {"XXX", -1,}};


        CreateBuffer(&buf, &cmd, input_file);
        
        Assembler(&buf, &cmd, Labels);

        buf.binary_position = 0;
        buf.position = 0;

        Assembler(&buf, &cmd, Labels);

        OutputBinary(&buf, output_file);
    
        DeleteBuffer(&buf, &cmd);
        return 0;
    }
    else
    {
        return 1;
    }
}
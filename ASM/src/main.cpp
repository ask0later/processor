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
        //printf("first_____________________________________________\n");
        
        Assembler(&buf, &cmd, Labels);
        buf.binary_position = 0;
        buf.position = 0;

        // printf("%d = %s\n", Labels[0].value_ptr, Labels[0].name);
        // printf("%d = %s\n", Labels[1].value_ptr, Labels[1].name);
        // printf("%d = %s\n", Labels[2].value_ptr, Labels[2].name);
        // printf("%d = %s\n", Labels[3].value_ptr, Labels[3].name);
        // printf("%d = %s\n", Labels[4].value_ptr, Labels[4].name);
        // printf("%d = %s\n", Labels[5].value_ptr, Labels[5].name);
        // printf("%d = %s\n", Labels[6].value_ptr, Labels[6].name);
        // printf("%d = %s\n", Labels[7].value_ptr, Labels[7].name);
        // printf("%d = %s\n", Labels[8].value_ptr, Labels[8].name);
        // printf("%d = %s\n", Labels[9].value_ptr, Labels[9].name);
        
        // printf("second____________________________________________\n");
        
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
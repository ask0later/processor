#include "readFile.h"
#include "asm.h"


int main(const int argc, const char* argv[])
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
        
        int error_code1 = Assembler(&buf, &cmd, Labels);
        if (DumpErrors(error_code1, &buf, &cmd) != 0)
        {
            DeleteBuffer(&buf, &cmd);
            return 1;
        }

        buf.binary_position = 0;
        buf.position = 0;
        buf.nline = 0;
        int error_code2 = Assembler(&buf, &cmd, Labels);
        if (DumpErrors(error_code2, &buf, &cmd) != 0)
        {
            DeleteBuffer(&buf, &cmd);
            return 1;
        }
        
        OutputBinary(&buf, output_file);
        DeleteBuffer(&buf, &cmd);
        return 0;
    }
    
    return 1;
}
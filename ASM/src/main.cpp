#include "readFile.h"
#include "asm.h"

// arg[1] - input_file
int main()
{
    struct Text    buf = {};
    struct Command cmd = {};
     

    CreateBuffer(&buf, &cmd);
    Assembler(&buf, &cmd);


    DeleteBuffer(&buf, &cmd);
}
#include "readCmd.h"
#include "stack.h"
#include "processor.h"

int main(const int argc, const char* argv[])
{
    if (argc == 2)
    {
        const char* binary = argv[1];
        struct Text      cmd = {};
        struct Proc      spu = {};

        CreateBuffer(&cmd, binary);
        StackCtor(&(spu.stk));
        StackCtor(&(spu.adress));
    
        Processor(&spu, &cmd);

        StackDtor(&(spu.adress));
        StackDtor(&(spu.stk));
        DeleteBuffer(&cmd);
        return 0;
    }
    printf("error: insufficient number of command line arguments\n");
    
    return 1;
}
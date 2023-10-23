#include "commandReading.h"
#include "disassembler.h"


int main()
{
    struct Text cmds;
    CreateBuffer(&cmds);
    
    DisAssembler(&cmds);
    
    DeleteBuffer(&cmds);
}
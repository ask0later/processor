#include "readCmd.h"

const char* input_file = "../binary";

void CreateBuffer(Text* cmd, const char* binary)
{
    cmd->sizebuf = Get_Size_File(binary);

    cmd->position = 0;
    
    cmd->buffer = (char*) calloc(cmd->sizebuf, sizeof(char));
    
    Read_Binary_File(cmd, binary);
}

void DeleteBuffer(Text* cmd)
{
    free(cmd->buffer);
    cmd->sizebuf = INT_MAX;
}

void Read_Binary_File(Text* cmd, const char* binary)
{
    FILE* fname = fopen(binary, "r");

    fread(cmd->buffer, sizeof(char), cmd->sizebuf, fname);
    
    fclose(fname);
}

size_t Get_Size_File(const char* binary)
{
    struct stat buff = {};
    stat(binary, &buff);
    return (size_t) (buff.st_size + 1);
}
#include "readCmd.h"

const char* input_file = "../binary";

void CreateBuffer(Text* cmd)
{
    cmd->sizebuf = Get_Size_File();

    cmd->position = 0;
    
    cmd->buffer = (char*) calloc(cmd->sizebuf, sizeof(char));
    
    Read_Binary_File(cmd);
}

void DeleteBuffer(Text* cmd)
{
    free(cmd->buffer);
    cmd->sizebuf = INT_MAX;
}

void Read_Binary_File(Text* cmd)
{
    FILE* fname = fopen(input_file, "r");

    fread(cmd->buffer, sizeof(char), cmd->sizebuf, fname);
    
    fclose(fname);
}

size_t Get_Size_File()
{
    struct stat buff = {};
    stat(input_file, &buff);
    return (size_t) (buff.st_size + 1);
}
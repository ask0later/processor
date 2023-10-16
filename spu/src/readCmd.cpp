#include "readCmd.h"

const char* input_file = "../bytebinarycode";

void CreateBuffer(Text* buf)
{
    buf->sizebuf = Get_Size_File();
    
    buf->buffer = (char*) calloc(buf->sizebuf, sizeof(char));
    
    Read_Binary_File(buf);
}
void DeleteBuffer(Text* buf)
{
    free(buf->buffer - buf->sizebuf + 1);
    buf->sizebuf = INT_MAX;
}
void Read_Binary_File(Text* buf)
{
    FILE* fname = fopen(input_file, "r");

    fread(buf->buffer, sizeof(char), buf->sizebuf, fname);
    
    fclose(fname);
}


size_t Get_Size_File()
{
    struct stat buff = {};
    stat(input_file, &buff);
    return (size_t) (buff.st_size);
}


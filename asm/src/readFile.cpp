#include "readFile.h"

const size_t MAX_SIZE_REGISTR =   5;
const size_t MAX_SIZE_COMMAND =  10;
const size_t MAX_SIZE_LABEL   =  10;
const size_t SIZEBINARY       = 255;




void CreateBuffer(Text* buf, Command* cmd, const char*  input_file)
{
    buf->sizebuf = Get_Size_File(input_file);
    buf->nlines  = 0;
    
    buf->buffer     = (char*) calloc(buf->sizebuf, sizeof(char));
    buf->binarycode = (char*) calloc(256,          sizeof(char));
    
    buf->binary_position = 0;

    Read_Commands(buf, input_file);
    buf->nlines = Get_Num_Line(buf);

    cmd->code           =       0;
    cmd->value          = INT_MAX;

    cmd->command_name = (char*) calloc(MAX_SIZE_COMMAND, sizeof(char));
    cmd->reg          = (char*) calloc(MAX_SIZE_REGISTR, sizeof(char));
}

void DeleteBuffer(Text* buf, Command* cmd)
{
    buf->sizebuf = INT_MAX;
    buf->nlines  = INT_MAX;

    cmd->code = (char) MAX_IN_BYTE;

    free(buf->buffer      );
    free(cmd->command_name);
    free(cmd->reg         );
    free(buf->binarycode  );
}
void Read_Commands(Text* buf, const char* input_file)
{
    FILE* fname = fopen(input_file, "r");

    fread(buf->buffer, sizeof(char), buf->sizebuf, fname);
    
    fclose(fname);
}


size_t Get_Size_File(const char* input_file)
{
    struct stat    buff;
    stat(input_file, &buff);
    
    return (size_t) (buff.st_size + 1);
}

size_t Get_Num_Line(Text* buf)
{
    size_t size_nlines = 0;
    for (size_t counter = 0; counter < buf->sizebuf; counter++)
    {
        if (*(buf->buffer + counter) == '\n')
        {
            size_nlines++;
        }
    }
    return size_nlines + 1;
}

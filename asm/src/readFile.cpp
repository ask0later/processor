#include "readFile.h"

ProcessorError CreateBuffer(Text* buf, Command* cmd, const char*  input_file)
{
    buf->size_buffer = Get_Size_File(input_file);

    buf->num_lines  = 0;
    buf->num_line   = 0;
    
    buf->buffer     = (char*) calloc(buf->size_buffer, sizeof(char));
    if (buf->buffer == NULL) {return ProcessorALLOC_ERROR;}

    buf->binary_code = (char*) calloc(MAX_SIZE_BUFFER, sizeof(char));
    if (buf->binary_code == NULL) {return ProcessorALLOC_ERROR;}

    
    
    buf->binary_position = 0;

    ReadFile(buf, input_file);
    

    buf->num_lines = Get_Num_Line(buf);


    buf->start_line = GetStartLine(buf);

    if (buf->start_line == NULL) {return ProcessorALLOC_ERROR;}
    

    cmd->code           =       0;
    cmd->value          = INT_MAX;

    cmd->command_name = (char*) calloc(MAX_SIZE_ARGUMENT, sizeof(char));
    if (cmd->command_name == NULL) {return ProcessorALLOC_ERROR;}
    cmd->reg          = (char*) calloc(MAX_SIZE_ARGUMENT, sizeof(char));
    if (cmd->reg == NULL) {return ProcessorALLOC_ERROR;}
    cmd->argument     = (char*) calloc(MAX_SIZE_ARGUMENT, sizeof(char));
    if (cmd->argument == NULL) {return ProcessorALLOC_ERROR;}

    return ProcessorNO_ERROR;
}

void DeleteBuffer(Text* buf, Command* cmd)
{
    buf->size_buffer = INT_MAX;
    buf->num_lines   = INT_MAX;

    cmd->code = (char) MAX_IN_BYTE;

    free(buf->start_line  );
    free(buf->buffer      );
    free(cmd->command_name);
    free(cmd->reg         );
    free(buf->binary_code );
    free(cmd->argument    );
}


void ReadFile(Text* buf, const char* input_file)
{
    FILE* fname = fopen(input_file, "r");

    fread(buf->buffer, sizeof(char), buf->size_buffer, fname);
    
    fclose(fname);
}

char** GetStartLine(Text* buf)
{   
    char** array_start = (char**) calloc(buf->num_lines, sizeof(char*));
    size_t size_nlines = 1;
    array_start[0] = buf->buffer;
    for (size_t counter = 0; counter < buf->size_buffer; counter++)
    {
        if (*(buf->buffer + counter) == '\n')
        {
            array_start[size_nlines] = buf->buffer + counter + 1;
            *(buf->buffer + counter) = '\0';
            size_nlines++;
        }
    }
    
    return array_start;
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
    for (size_t counter = 0; counter < buf->size_buffer; counter++)
    {
        if (*(buf->buffer + counter) == '\n')
        {
            size_nlines++;
        }
    }
    return size_nlines + 1;
}

#include "commandReading.h"


void CreateBuffer(Text* cmds)
{
    cmds->sizebuf = Get_Size_File();
    cmds->nline = 0;
    
    cmds->buffer = (char*)calloc(cmds->sizebuf, sizeof(char));
    
    Read_Commands(cmds);
    cmds->nline = Get_Num_Line(cmds);

    cmds->ptr_to_line = (char**)calloc(cmds->nline, sizeof(char*));
    LinealizeCommands(cmds);
}
void DeleteBuffer(Text* cmds)
{
    cmds->sizebuf = INT_MAX;
    cmds->nline = INT_MAX;

    free(cmds->buffer);
    free(cmds->ptr_to_line);
}
void Read_Commands(Text* cmds)
{
    FILE* fname = fopen("../BYTEcodefile.txt", "r");

    fread(cmds->buffer, sizeof(char), cmds->sizebuf, fname);
    fclose(fname);
}

void LinealizeCommands(Text* cmds)
{
    *(cmds->ptr_to_line + 0) = cmds->buffer + 0;

    size_t counter_nline = 1;
    for (size_t counter_buf = 0; counter_buf < cmds->sizebuf; counter_buf++)
    {
        if ((cmds->buffer[counter_buf]) == '\n')
        {
            cmds->buffer[counter_buf] = '\0';
            cmds->ptr_to_line[counter_nline] = cmds->buffer + counter_buf + 1;
            counter_nline++;
        }
    }
}

size_t Get_Size_File()
{
    struct stat buff;
    stat("../BYTEcodefile.txt", &buff);
    return (size_t) (buff.st_size + 1);
}

size_t Get_Num_Line(Text* cmds)
{
    size_t size_nline = 0;
    for (size_t counter = 0; counter < cmds->sizebuf; counter++)
    {
        if (*(cmds->buffer + counter) == '\n')
        {
            size_nline++;
        }
    }
    return size_nline + 1;
}

#ifndef COMMANDREADlib
#define COMMANDREADlib
#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <assert.h>
#include <climits>

struct Text
{
    size_t nline;
    char** ptr_to_line;
    size_t sizebuf;
    char* buffer;
};

void CreateBuffer(Text* cmds);
void DeleteBuffer(Text* cmds);
void Read_Commands(Text* cmds);
void LinealizeCommands(Text* cmds);
size_t Get_Size_File();
size_t Get_Num_Line(Text* cmds);
#endif
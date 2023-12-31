#ifndef COMMANDREADlib
#define COMMANDREADlib

#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <assert.h>
#include <climits>

#include "../../enum.h"

struct Text
{
    size_t  sizebuf;
    char*    buffer;
    
    size_t position;

    int*    codebuf;
    size_t  counter;
};

void     CreateBuffer(Text* buf, const char* binary);
void     DeleteBuffer(Text* buf);
void Read_Binary_File(Text* buf, const char* binary);

size_t  Get_Size_File(const char* binary);
#endif
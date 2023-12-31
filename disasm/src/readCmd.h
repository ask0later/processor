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
    size_t sizebuf;
    char* buffer;
    
    size_t position;

    int* codebuf;
    size_t counter;

    size_t num_label;
};


void     CreateBuffer(Text* buf);
void     DeleteBuffer(Text* buf);

void Read_Binary_File(Text* buf);

size_t Get_Size_File();
#endif
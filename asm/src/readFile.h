#ifndef COMMANDREADlib
#define COMMANDREADlib

#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <assert.h>
#include <climits>

#include "../../commands.h"

const unsigned char MAX_IN_BYTE   = 255;
const size_t        NUM_LABELS    =  10;
const size_t        SIZE_ARGUMENT =  10;

struct Text
{
    size_t           nlines;
    size_t          sizebuf;
    char*            buffer;
    size_t         position;

    char*        binarycode;
    int     binary_position;
};

struct Command
{
    char               code;
    char*      command_name;
    char*               reg;
    int               value;
    size_t   numberlabelcmd;
};

struct OneCommand
{
    char name[SIZE_ARGUMENT];
    int        argument_type;
    int            valueName;
};

struct Label
{
    char name[SIZE_ARGUMENT];
    int            value_ptr;
};

void  CreateBuffer(Text* buf, Command* cmd, const char*  input_file);
void  DeleteBuffer(Text* buf, Command* cmd);
void Read_Commands(Text* buf, const char*  input_file);

size_t Get_Size_File(const char*  input_file);
size_t Get_Num_Line(Text* buf);

#endif
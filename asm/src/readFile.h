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



enum ProcessorError
{
    ProcessorNO_ERROR,
    ProcessorALLOC_ERROR,
    Processor
};

const unsigned char MAX_IN_BYTE    =  255;
const size_t        NUM_LABELS     =   30;
const size_t   MAX_SIZE_BUFFER     = 2048;

const size_t     MAX_SIZE_ARGUMENT =  50;
const size_t     SIZEBINARY        = 255;
const size_t     REF_SIZE_REGISTR  =   3;
const size_t     REF_SIZE_COMMAND  =  10;
const size_t     REF_SIZE_LABEL    =  10;
const size_t     REF_SIZE_ARGUMENT =  10;


struct Text
{
    size_t        num_lines;
    size_t         num_line;

    size_t      size_buffer;
    char*            buffer;
    char**       start_line;

    char*       binary_code;
    int     binary_position;
};

struct Command
{
    char*      command_name;
    char*          argument;

    char               code;
    char*               reg;
    int               value;
    
    size_t       num_labels;
};

struct OneCommand
{
    char name[MAX_SIZE_ARGUMENT];
    int            argument_type;
    int               value_name;
};

struct Label
{
    char name[MAX_SIZE_ARGUMENT];
    int                value_ptr;
};

ProcessorError  CreateBuffer(Text* buf, Command* cmd, const char*  input_file);
void  DeleteBuffer(Text* buf, Command* cmd                         );
void ReadFile(Text* buf,               const char*  input_file);

char** GetStartLine(Text* buf);
size_t                        Get_Size_File(const char*  input_file);
size_t                         Get_Num_Line(Text* buf              );

#endif
#include "disassembler.h"

void DisAssembler(Text* cmds)
{
    int command = INT_MAX;
    FILE* fp = fopen("../ASMfile.txt", "a");
    for (size_t counter = 0; counter < cmds->nline; counter++)
    {
        sscanf(*(cmds->ptr_to_line + counter), "%d", &command);
        int argument = 0;

        switch(command)
        {
            case PUSH:
                fprintf(fp, "push");
                sscanf(*(cmds->ptr_to_line + counter), "%d%d", &command, &argument);
                fprintf(fp, " %d\n", argument);
                break;
            case POP:
                fprintf(fp, "pop\n");
                break;
            case ADD:
                fprintf(fp, "add\n");
                break;
            case SUB:
                fprintf(fp, "sub\n");
                break;
            case MUL:
                fprintf(fp, "mul\n");
                break;
            case DIV:
                fprintf(fp, "div\n");
                break;
            case SQRT:
                fprintf(fp, "sqrt\n");
                break;
            case SIN:
                fprintf(fp, "sin\n");
                break;
            case COS:
                fprintf(fp, "cos\n");
                break;
            case IN:
                fprintf(fp, "in");
                sscanf(*(cmds->ptr_to_line + counter), "%d%d", &command, &argument);
                printf(" %d\n", argument);
                break;
            case OUT:
                fprintf(fp, "out\n");
                break;
            case HTL:
                fprintf(fp, "htl\n");
                break;
            default:
                break;
        }
    }
    fclose(fp);
}
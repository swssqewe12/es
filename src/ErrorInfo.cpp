#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include "ErrorInfo.h"

ErrorInfo ErrInf(unsigned int ln, unsigned char col, const char* fn)
{
    ErrorInfo errinf;
    errinf.ln = ln;
    errinf.col = col;
    errinf.fn = fn;
    return errinf;
}

void getFileLine(char* line, size_t line_size, const char* fn, unsigned int ln)
{   
    FILE* file;
    if ((file = fopen(fn, "r")) == NULL)
    {
        *line = '\0';
        return;
    }
    
    while (ln > 0 && fgets(line, line_size, file) != NULL)
        ln--;
    
    int line_len_mo = strlen(line) - 1;
    if (line[line_len_mo] == '\n')
        line[line_len_mo] = '\0';
    
    fclose(file);
}

void RaiseErr(ErrorInfo errinf, const char* msg)
{
    system("@cls||clear");
    char* spaces = (char*) malloc(errinf.col);
    memset(spaces, ' ', errinf.col - 1);
    spaces[errinf.col - 1] = '\0';
    char line[256];
    getFileLine(line, sizeof(line), errinf.fn, errinf.ln);
    printf("An error has occured in \"%s\"\n\n%s\nLn:%d  Col:%d\n\n%s\n%s^", errinf.fn, msg, errinf.ln, errinf.col, &line, spaces);
    exit(EXIT_FAILURE);
}
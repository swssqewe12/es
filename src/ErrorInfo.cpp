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
    FILE* file = fopen(fn, "r");
    
    if (file == NULL)
        *line = '\0';
    
    while (ln > 0 && fgets(line, line_size, file) != NULL)
        ln--;
    
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
    printf("An error has occured in \"%s\"\n\nError: %s\nLn:%d  Col:%d\n\n%s\n%s^", errinf.fn, msg, errinf.ln, errinf.col, &line, spaces);
    exit(EXIT_FAILURE);
}
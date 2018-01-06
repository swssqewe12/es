#include <stdio.h>
#include <cstdlib>
#include "ErrorInfo.h"

ErrorInfo ErrInf(unsigned int ln, unsigned char col, const char* fn)
{
    ErrorInfo errinf;
    errinf.ln = ln;
    errinf.col = col;
    errinf.fn = fn;
    return errinf;
}

void RaiseErr(ErrorInfo errinf, const char* msg)
{
    printf("An error has occured in \"%s\"\n\nError: %s\nLn:%u  Col:%u\n\n", errinf.fn, msg, errinf.ln, errinf.col);
    fflush(stdout);
    exit(EXIT_FAILURE);
}
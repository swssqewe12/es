#include "ErrorInfo.h"

ErrorInfo ErrInf(unsigned int ln, unsigned char col, const char* fn)
{
    ErrorInfo errinf;
    errinf.ln = ln;
    errinf.col = col;
    errinf.fn = fn;
}
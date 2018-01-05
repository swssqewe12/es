#pragma once

struct ErrorInfo
{
    unsigned int ln;
    unsigned char col;
    const char* fn;
};

extern ErrorInfo ErrInf(unsigned int ln, unsigned char col, const char* fn);
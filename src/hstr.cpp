#include <stdlib.h>
#include <cstring>
#include "hstr.h"
#define HSTR_STEP 128;

int roundUp(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = abs(numToRound) % multiple;
    if (remainder == 0)
        return numToRound;

    if (numToRound < 0)
        return -(abs(numToRound) - remainder);
    else
        return numToRound + multiple - remainder;
}

//////////////////////////////////////////////////

hstr::hstr()
{
    cap = 0;
    length = 0;
    step = HSTR_STEP;
    chars = NULL;
}

hstr::hstr(const hstr& h_str)
{
    cap = 0;
    length = 0;
    step = HSTR_STEP;
    chars = NULL;
    append(h_str);
}

hstr::hstr(char* c_str)
{
    cap = 0;
    step = HSTR_STEP;
    chars = NULL;
    append(c_str);
}

hstr::hstr(char c)
{
    cap = 0;
    step = HSTR_STEP;
    chars = NULL;
    append(c);
}

void hstr::append(const hstr& h_str)
{
    if (h_str.length > 0)
    {
        int len = length + h_str.length;
        int last_cap = cap;
        cap = roundUp(len, step);
        if (last_cap != cap)
            chars = (char*) realloc(chars, cap);
        memcpy(chars + length, h_str.chars, h_str.length);
        length = len;
    }
}

void hstr::append(char* c_str)
{
    int c_str_len = strlen(c_str);
    int len = length + c_str_len;
    int last_cap = cap;
    cap = roundUp(len, step);
    if (last_cap != cap)
        chars = (char*) realloc(chars, cap);
    memcpy(chars + length, c_str, c_str_len);
    length = len;
}

void hstr::append(char c)
{
    int len = length + 1;
    int last_cap = cap;
    cap = roundUp(len, step);
    if (last_cap != cap)
        chars = (char*) realloc(chars, cap);
    chars[len - 1] = c;
    length = len;
}

void hstr::shrink_unused()
{
    if (cap != length)
    {
        cap = length;
        chars = (char*) realloc(chars, length);
    }
}

char* hstr::c_str()
{
    char* c_str = (char*) malloc(length + 1);
    memcpy(c_str, chars, length);
    c_str[length] = '\0';
    return c_str;
}

hstr::~hstr()
{
    if (chars)
        free(chars);
}

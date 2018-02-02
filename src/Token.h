#pragma once

#include "ErrorInfo.h"

enum TokenType
{
    ID,
    STRING,
    LPAREN,
    RPAREN,
    SEMI,
    EQ,
    DOT,
    COMMA,
    NUMBER
};

extern const char* TokenTypeStrings[];

class Token
{
    public:
        enum TokenType type;
        char* value;
        ErrorInfo errinf;

        Token(enum TokenType type, char* value, ErrorInfo errinf);
        Token(enum TokenType type, ErrorInfo errinf);
};

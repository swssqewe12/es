#pragma once

enum TokenType
{
    ID,
    STRING,
    LPAREN,
    RPAREN,
    SEMI
};

extern const char* TokenTypeStrings[];

class Token
{
    public:
        enum TokenType type;
        char* value;

        Token(enum TokenType type, char* value);
        Token(enum TokenType type);
};

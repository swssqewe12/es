#include <cstddef>
#include "Token.h"

const char* TokenTypeStrings[] = {
    "ID",
    "STRING",
    "LPAREN",
    "RPAREN",
    "SEMI",
    "EQ",
    "DOT"
};

Token::Token(enum TokenType type, char* value, ErrorInfo errinf)
{
    this->type = type;
    this->value = value;
    this->errinf = errinf;
}

Token::Token(enum TokenType type, ErrorInfo errinf)
{
    this->type = type;
    this->value = NULL;
    this->errinf = errinf;
}

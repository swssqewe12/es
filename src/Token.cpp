#include <cstddef>
#include "Token.h"

const char* TokenTypeStrings[] = {
    "ID",
    "STRING",
    "LPAREN",
    "RPAREN",
    "SEMI"
};

Token::Token(enum TokenType type, char* value)
{
    this->type = type;
    this->value = value;
}

Token::Token(enum TokenType type)
{
    this->type = type;
    this->value = NULL;
}

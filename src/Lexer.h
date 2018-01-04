#pragma once

#include <stdio.h>
#include "List.h"
#include "Token.h"

class Lexer
{
    public:
        Lexer(FILE* file);
        void make_tokens(List<Token>& tokens);
        char* make_string();
        char* make_identifier();
    private:
        FILE* file;
        bool notEOF;
        char c;

        void advance();
};

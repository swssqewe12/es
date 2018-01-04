#pragma once

#include <stdio.h>
#include "List.h"
#include "Token.h"

class Lexer
{
    public:
        Lexer(FILE* file);
        List<Token>* make_tokens();
        char* make_string();
        char* make_identifier();
    private:
        FILE* file;
        bool notEOF;
        char c;

        void advance();
};

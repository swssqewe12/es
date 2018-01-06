#include <ctype.h>
#include "ErrorInfo.h"
#include "Lexer.h"
#include "hstr.h"

Lexer::Lexer(FILE* file)
{
    this->file = file;
    this->cur_fn = "res/script.es";
    this->cur_ln = 1;
    this->cur_col = 0;
    this->errinf;
    advance();
}

void Lexer::make_tokens(List<Token>& tokens)
{
    while (notEOF)
    {
        if (isspace(c))
        {
            advance();
        }
        else if (c == '(')
        {
            *(tokens.push()) = Token(LPAREN, errinf);
            advance();
        }
        else if (c == ')')
        {
            *(tokens.push()) = Token(RPAREN, errinf);
            advance();
        }
        else if (c == ';')
        {
            *(tokens.push()) = Token(SEMI, errinf);
            advance();
        }
        else if (c == '"')
        {
            *(tokens.push()) = Token(STRING, make_string(), errinf);
        }
        else if (isalpha(c))
        {
            *(tokens.push()) = Token(ID, make_identifier(), errinf);
        }
        else
        {
            RaiseErr(errinf, "Illegal character");
        }
    }
}

char* Lexer::make_string()
{
    advance();
    hstr str;

    while (notEOF && c != '"')
    {
        str.append(c);
        advance();
    }

    advance();
    return str.c_str();
}

char* Lexer::make_identifier()
{
    hstr result;

    while (notEOF && isalpha(c))
    {
        result.append(c);
        advance();
    }

    return result.c_str();
}

void Lexer::advance()
{
    if (c == '\n')
    {
        cur_ln++;
        cur_col = 0;
    }

    int x = fgetc(file);
    notEOF = x != EOF;
    c = (unsigned char) x;
    cur_col++;

    errinf = ErrInf(cur_ln, cur_col, cur_fn);
}

#include <ctype.h>
#include "Lexer.h"
#include "hstr.h"

Lexer::Lexer(FILE* file)
{
    this->file = file;
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
            *(tokens.push()) = Token(LPAREN);
            advance();
        }
        else if (c == ')')
        {
            *(tokens.push()) = Token(RPAREN);
            advance();
        }
        else if (c == ';')
        {
            *(tokens.push()) = Token(SEMI);
            advance();
        }
        else if (c == '"')
        {
            *(tokens.push()) = Token(STRING, make_string());
        }
        else if (isalpha(c))
        {
            *(tokens.push()) = Token(ID, make_identifier());
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
    int x = fgetc(file);
    notEOF = x != EOF;
    c = (unsigned char) x;
}

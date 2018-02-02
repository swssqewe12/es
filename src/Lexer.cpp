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
    advance();
}

void Lexer::make_tokens(List<Token>& tokens)
{
    ErrorInfo errinf;

    while (notEOF)
    {  
        errinf = ErrInf(cur_ln, cur_col, cur_fn);

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
        else if (c == '=')
        {
            *(tokens.push()) = Token(EQ, errinf);
            advance();
        }
        else if (c == '.')
        {
            *(tokens.push()) = Token(DOT, errinf);
            advance();
        }
        else if (c == ',')
        {
            *(tokens.push()) = Token(COMMA, errinf);
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
        else if (c >= '0' && c <= '9')
        {
            *(tokens.push()) = Token(NUMBER, make_number(), errinf);
        }
        else
        {
            RaiseErr(errinf, "Error: Illegal character");
        }
    }
}

char* Lexer::make_string()
{
    advance();
    int state;
    // 0 - default | 1 - backslash
    hstr str;

    while (notEOF && (c != '"' || state != 0))
    {
        if (state == 0)
        {
            if (c == '\\')
            {
                state = 1;
                advance();
                continue;
            }
            
            str.append(c);
            advance();
        }
        else if (state == 1)
        {
            state = 0;

            switch (c)
            {
                case 'n':
                    str.append('\n');
                break;
                case 'r':
                    str.append('\r');
                break;
                case 't':
                    str.append('\t');
                break;
                case 'b':
                    str.append('\b');
                break;
                default:
                    str.append(c);
                break;
            }

            advance();
        }
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

char* Lexer::make_number()
{
    hstr result;

    while (notEOF && c >= '0' && c <= '9')
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
}

#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "ErrorInfo.h"

Parser::Parser(List<Token>& tokens): tokens(tokens)
{
    this->tok_index = 0;
}

Token* Parser::eat(TokenType tok_type)
{
    Token* tok = tokens.get(tok_index);
    
    if (tok->type == tok_type)
    {
        tok_index++;
        return tok;
    }

    eatError(tok, tok_type);
}

void Parser::eatError(Token* tok, TokenType tok_type)
{
    int buffer_size = 36 + strlen(TokenTypeStrings[tok_type]) + 1;
    char* buffer = (char*) malloc(buffer_size);
    snprintf(buffer, buffer_size, "Invalid syntax: Expected Token Type %s", TokenTypeStrings[tok_type]);
    RaiseErr(tok->errinf, buffer);
}

ProgramTree* Parser::parse()
{
    return program();
}

/////////////////////////////////////////

ProgramTree* Parser::program()
{
    ProgramTree* tree = new ProgramTree();
    tree->statements = List<Statement>();
    statements(tree->statements);
    return tree;
}

void Parser::statements(List<Statement>& list)
{
    while (tok_index < tokens.length)
    {
        Token* func_tok = eat(ID);
        eat(LPAREN);
        Token* str_tok = eat(STRING);
        eat(RPAREN);
        eat(SEMI);

        FuncCallNode* node = new FuncCallNode();
        node->name     = func_tok;
        node->argument = str_tok;

        Statement* statement = list.push();
        statement->type = FUNC_CALL;
        statement->node = node;
    }
}
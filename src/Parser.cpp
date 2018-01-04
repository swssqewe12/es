#include <string.h>
#include <stdio.h>
#include "Parser.h"

Parser::Parser(List<Token>* tokens)
{
    this->tokens = tokens;
    this->tok_index = 0;
}

Token* Parser::eat(TokenType tok_type)
{
    Token* tok = tokens->get(tok_index);
    
    if (tok->type == tok_type)
    {
        tok_index++;
        return tok;
    }
}

ProgramTree* Parser::parse()
{
    return program();
}

/////////////////////////////////////////

ProgramTree* Parser::program()
{
    ProgramTree* tree = new ProgramTree();
    tree->statements = statements();
    return tree;
}

List<Statement> Parser::statements()
{
    List<Statement> statements;

    while (tok_index < tokens->length)
    {
        Token* func_tok = eat(ID);
        eat(LPAREN);
        Token* str_tok = eat(STRING);
        eat(RPAREN);
        eat(SEMI);

        FuncCallNode* node = new FuncCallNode();
        node->argument = str_tok->value;

        Statement* statement = new Statement();
        statement->type = FUNC_CALL;
        statement->node = node;

        statements.push(statement);
    }

    return statements;
}
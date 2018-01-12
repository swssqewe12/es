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

Token* Parser::tryeat(TokenType tok_type)
{
    Token* tok = tokens.get(tok_index);

    if (tok->type == tok_type)
    {
        tok_index++;
        return tok;
    }

    return NULL;
}

void Parser::eatError(Token* tok, TokenType tok_type)
{
    int buffer_size = 36 + strlen(TokenTypeStrings[tok_type]) + 1;
    char* buffer = (char*) malloc(buffer_size);
    snprintf(buffer, buffer_size, "Invalid Syntax: Expected Token Type %s", TokenTypeStrings[tok_type]);
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
    tree->declarations = List<Declaration>();
    statements(tree->statements, tree->declarations);
    return tree;
}

void Parser::statements(List<Statement>& statements, List<Declaration>& declarations)
{
    while (tok_index < tokens.length)
    {
        Token* id_tok = eat(ID);
        
        if (tryeat(LPAREN))
        {
            FuncCallNode* node = new FuncCallNode();
            node->name     = id_tok;

            Statement* statement = statements.push();
            statement->type = StatementType::FUNC_CALL;
            statement->node = node;

            Token* tok;
            Expression arg;

            if (tok = tryeat(STRING))
            {
                arg.type = ExprType::STRING;
                arg.node = tok;
            }
            else if (tok = tryeat(ID))
            {
                arg.type = ExprType::VARIABLE;
                arg.node = tok;
            }
            else
            {
                tok_index++;
                RaiseErr(tokens.get(tok_index)->errinf, "Invalid Syntax: Expected Token Type STRING or ID");
            }
            
            node->argument = arg;
            eat(RPAREN);
            eat(SEMI);
        }
        else if(strcmp(id_tok->value, "var") == 0)
        {
            Token* var_tok = eat(ID);
            eat(SEMI);

            Declaration* declaration = declarations.push();
            declaration->name = var_tok;
        }
        else
        {
            tok_index++;
            RaiseErr(tokens.get(tok_index)->errinf, "Invalid Syntax: Expected Token Type LPAREN");
        }
    }
}
#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "ErrorInfo.h"

Parser::Parser(List<Token>& tokens): tokens(tokens)
{
    this->tok_index = 0;
}

Token* Parser::eat()
{
    Token* tok = tokens.get(tok_index);
    tok_index++;
    return tok;
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
    int buffer_size = 25 + strlen(TokenTypeStrings[tok_type]) + 1;
    char* buffer = (char*) malloc(buffer_size);
    snprintf(buffer, buffer_size, "Invalid Syntax: Expected %s", TokenTypeStrings[tok_type]);
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
        Token* current_tok = tokens.get(tok_index);
        if (current_tok->type == ID && strcmp(current_tok->value, "var") == 0)
        {
            eat();
            Declaration* declaration = declarations.push();
            declaration->name = eat(ID);

            if (!tryeat(SEMI))
            {
                eat(EQ);
                Token* num = eat(NUMBER);
                Statement* statement = statements.push();
                statement->type = VAR_ASSING;
                statement->value = VarAssignNode();
                statement->value->varln = VariableNameLink();
                eat(SEMI);
            }
        }
        else if (current_tok->type == ID)
        {
            Statement* s = statements.push();
            statement(s);
        }
        else
        {
            //tok_index++;
            RaiseErr(tokens.get(tok_index)->errinf, "Invalid Syntax: Expected identifier");
        }
    }
}

void Parser::statement(Statement* s)
{
    VariableNameLink varnl;
    variableNameLink(&varnl);

    s->type = StatementType::FUNC_CALL;
    FuncCallNode* node = new FuncCallNode();
    node->varnl = varnl;
    s->node = node;
    Expression arg;
    
    node->args = passedArguments();
    eat(SEMI);
}

List<Expression>* Parser::passedArguments()
{
    eat(LPAREN);
    bool comma_state = false;
    Token* tok;
    List<Expression>* args = new List<Expression>();

    while (tokens.get(tok_index)->type != RPAREN)
    {
        if (comma_state)
        {
            eat(COMMA);
        }

        Expression arg;

        if (Token* str_tok = tryeat(STRING))
        {
            arg.type = ExprType::STRING;
            arg.node = str_tok;
        }
        else if (tokens.get(tok_index)->type == ID)
        {
            VariableNameLink* varnl = new VariableNameLink();
            variableNameLink(varnl);
            arg.type = ExprType::VARIABLE;
            arg.node = varnl;
        }
        else
        {
            tok_index++;
            RaiseErr(tokens.get(tok_index)->errinf, "Invalid Syntax: Expected string or identifier");
        }

        args->push(arg);
        comma_state = true;
    }

    eat();
    return args;
}

void Parser::variableNameLink(VariableNameLink* varnl)
{
    varnl->tok = eat(ID);
    if (Token* tok = tryeat(DOT))
        variableNameLink(varnl->next);
}
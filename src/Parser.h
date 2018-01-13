#pragma once

#include "List.h"
#include "Token.h"
#include "Node.h"
#include "VariableNameLink.h"

class Parser
{
    public:
        Parser(List<Token>& tokens);
        ProgramTree* parse();
    
    private:
        List<Token>& tokens;
        size_t tok_index;
        Token* eat(TokenType tok_type);
        Token* eat();
        Token* tryeat(TokenType tok_type);
        void eatError(Token* tok, TokenType tok_type);
        ProgramTree* program();
        void statements(List<Statement>& list, List<Declaration>& declarations);
        void statement(Statement* statement);
        void variableNameLink(VariableNameLink* varnl);
};
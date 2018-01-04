#pragma once

#include "List.h"
#include "Token.h"
#include "Node.h"

class Parser
{
    public:
        Parser(List<Token>* tokens);
        ProgramTree* parse();
    
    private:
        List<Token>* tokens;
        size_t tok_index;
        Token* eat(TokenType tok_type);
        ProgramTree* program();
        void statements(List<Statement>& list);
};
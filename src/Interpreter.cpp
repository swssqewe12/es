#include <string.h>
#include <stdio.h>
#include "Interpreter.h"
#include "ErrorInfo.h"
#include "VariableNameLink.h"

Interpreter::Interpreter()
{
    symbolTable = NULL;
}

void Interpreter::visit_ProgramTree(ProgramTree* tree)
{
    pushSymbolTable(symbolTable);
    
    for (int i = 0; i < tree->declarations.length; i++)
    {
        Declaration* declaration = tree->declarations.get(i);
        symbolTable->symbols[declaration->name->value] = NULL;
    }

    for (int i = 0; i < tree->statements.length; i++)
    {
        Statement* statement = tree->statements.get(i);

        switch (statement->type)
        {
            case StatementType::FUNC_CALL:
                visit_FuncCallNode((FuncCallNode*) statement->node);
            break;
        }
    }
}

void Interpreter::visit_FuncCallNode(FuncCallNode* node)
{
    if (strcmp(node->varnl.tok->value, "print") == 0)
    {
        Expression* arg = node->args->get(0);

        switch (arg->type)
        {
            case ExprType::STRING:
                puts(((Token*) arg->node)->value);
            break;
            case ExprType::VARIABLE:
                Token* name = ((VariableNameLink*) arg->node)->tok;
                auto it = symbolTable->symbols.find(name->value);
                if (it != symbolTable->symbols.end())
                    if (it->second == NULL)
                        printf("null");
                    else
                        printf("has value..");
                else
                    printf("Lol not defined.");
            break;
        }
    }
    else
    {
        int buffer_size = 15 + strlen(node->varnl.tok->value) + 1;
        char* buffer = (char*) malloc(buffer_size);
        snprintf(buffer, buffer_size, "%s is not defined", node->varnl.tok->value);
        RaiseErr(node->varnl.tok->errinf, buffer);
    }
}
#include <string.h>
#include <stdio.h>
#include "Interpreter.h"
#include "ErrorInfo.h"

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
    if (strcmp(node->name->value, "print") == 0)
    {
        switch (node->argument.type)
        {
            case ExprType::STRING:
                puts(((Token*) node->argument.node)->value);
            break;
            case ExprType::VARIABLE:
                puts("Hohoho");
            break;
        }
    }
    else
    {
        int buffer_size = 15 + strlen(node->name->value) + 1;
        char* buffer = (char*) malloc(buffer_size);
        snprintf(buffer, buffer_size, "%s is not defined", node->name->value);
        RaiseErr(node->name->errinf, buffer);
    }
}
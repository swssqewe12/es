#include <string.h>
#include <stdio.h>
#include "Interpreter.h"
#include "ErrorInfo.h"

Interpreter::Interpreter(){}

void Interpreter::visit_ProgramTree(ProgramTree* tree)
{
    for (int i = 0; i < tree->declarations.length; i++)
    {
        Declaration* declaration = tree->declarations.get(i);

        printf("NEW DECLARATION -> %s\n", declaration->name->value);
    }

    for (int i = 0; i < tree->statements.length; i++)
    {
        Statement* statement = tree->statements.get(i);

        switch (statement->type)
        {
            case FUNC_CALL:
                visit_FuncCallNode((FuncCallNode*) statement->node);
            break;
        }
    }
}

void Interpreter::visit_FuncCallNode(FuncCallNode* node)
{
    if (strcmp(node->name->value, "print") == 0)
    {
        puts(node->argument->value);
    }
    else
    {
        int buffer_size = 15 + strlen(node->name->value) + 1;
        char* buffer = (char*) malloc(buffer_size);
        snprintf(buffer, buffer_size, "%s is not defined", node->name->value);
        RaiseErr(node->name->errinf, buffer);
    }
}
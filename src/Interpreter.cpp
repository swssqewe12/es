#include <string.h>
#include <stdio.h>
#include "Interpreter.h"

Interpreter::Interpreter(){}

void Interpreter::visit_ProgramTree(ProgramTree* tree)
{
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
    if (strcmp(node->name, "print") == 0)
    {
        puts(node->argument);
    }
}
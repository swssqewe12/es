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
        visit_PrintFuncCallNode(node);
    }
    else if (strcmp(node->varnl.tok->value, "println") == 0)
    {
        visit_PrintFuncCallNode(node);
        putchar('\n');
    }
    else
    {
        int buffer_size = 15 + strlen(node->varnl.tok->value) + 1;
        char* buffer = (char*) malloc(buffer_size);
        snprintf(buffer, buffer_size, "%s is not defined", node->varnl.tok->value);
        RaiseErr(node->varnl.tok->errinf, buffer);
    }
}

void Interpreter::visit_PrintFuncCallNode(FuncCallNode* node)
{
    for (int i = 0; i < node->args->length; i++)
    {
        Expression* arg = node->args->get(i);

        switch (arg->type)
        {
            case ExprType::STRING:
                fputs(((Token*) arg->node)->value, stdout);
            break;
            case ExprType::VARIABLE:{
                Token* name = ((VariableNameLink*) arg->node)->tok;
                auto it = symbolTable->symbols.find(name->value);
                if (it != symbolTable->symbols.end())
                    if (it->second == NULL)
                        fputs("null", stdout);
                    else
                        printf("has value..");
                else
                    printf("Lol not defined.");
            }break;
            default:
                fputs("!ERR!", stdout);
            break;
        }
    }
}
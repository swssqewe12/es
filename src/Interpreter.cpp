#include <string.h>
#include <stdio.h>
#include "Interpreter.h"
#include "ErrorInfo.h"
#include "VariableNameLink.h"
#include "hstr.h"

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
    // TODO in far future -- my own strcmp function that if it doesn't match a string, it can start comparing the other string half way without having to start again!
    if (strcmp(node->varnl.tok->value, "print") == 0)
    {
        visit_PrintFuncCallNode(node);
    }
    else if (strcmp(node->varnl.tok->value, "println") == 0)
    {
        visit_PrintFuncCallNode(node);
        putchar('\n');
    }
    else if (strcmp(node->varnl.tok->value, "printf") == 0)
    {
        visit_PrintfFuncCallNode(node);
    }
    else if(strcmp(node->varnl.tok->value, "printfln") == 0)
    {
        visit_PrintfFuncCallNode(node);
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

void Interpreter::visit_PrintfFuncCallNode(FuncCallNode* node)
{

    if (node->args->length == 0)
        return;

    if (node->args->length == 1)
    {
        Expression* arg = node->args->get(0);
        if (arg->type == ExprType::STRING)
            fputs(((Token*)arg->node)->value, stdout);
        return;
    }

    Expression* arg = node->args->get(0);
    if (arg->type != ExprType::STRING)
        return;

    hstr str;
    int curr_arg = 0;
    char* c = ((Token*)arg->node)->value;
    int state = 0;
    // 0: default | 1: percentage

    while (*c != '\0')
    {
        if (state == 0)
        {
            if (*c == '%')
            {
                state = 1;
                c++;
                continue;
            }

            str.append(*c);
            c++;
        }
        else if (state == 1)
        {
            state = 0;
            curr_arg++;

            if (curr_arg < node->args->length)
            {
                Expression* arg = node->args->get(curr_arg);
                switch (*c)
                {
                    case 's':
                        switch (arg->type)
                        {
                            case ExprType::STRING:
                                str.append(((Token*) arg->node)->value);
                            break;
                        }
                    break;
                    case 'd':
                        switch (arg->type)
                        {
                            case ExprType::STRING:
                                str.append("unf"); //unformattable
                            break;
                            case ExprType::VARIABLE:
                                str.append("null");
                            break;
                            default:
                                str.append("unf");
                            break;
                        }
                    break;
                    default:
                        str.append('%');
                        str.append(*c);
                    break;
                }
            }
            else
            {
                str.append('%');
                str.append(*c);
            }

            c++;
        }
    }

    fputs(str.c_str(), stdout);
}
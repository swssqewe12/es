#pragma once

#include "Token.h"

#include "List.h"

enum StatementType
{
    FUNC_CALL
};

struct Statement
{
    StatementType type;
    void* node;
};

struct Declaration
{
    Token* name;
};

struct ProgramTree
{
    List<Statement> statements;
    List<Declaration> declarations;
};

struct FuncCallNode
{
    Token* name;
    // Obviously in the future function call nodes will have list of arguments etc, whereas since print is the only current func, there will be only one argument : string
    Token* argument;
};
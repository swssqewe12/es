#pragma once

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

struct ProgramTree
{
    List<Statement> statements;
};

struct FuncCallNode
{
    char* name;
    // Obviously in the future function call nodes will have list of arguments etc, whereas since print is the only current func, there will be only one argument : string
    char* argument;
};
#pragma once

#include "Token.h"

#include "List.h"

enum class StatementType
{
    FUNC_CALL
};

enum class ExprType
{
    VARIABLE,
    STRING
};

struct Statement
{
    StatementType type;
    void* node;
};

struct Expression
{
    ExprType type;
    void* node;
};

///

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
    Expression argument;
};
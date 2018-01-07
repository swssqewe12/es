#pragma once

struct SymbolTable
{
    int depth;
    SymbolTable* parent;
};

extern void pushSymbolTable(SymbolTable*& symbolTable);
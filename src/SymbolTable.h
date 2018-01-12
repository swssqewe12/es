#pragma once
#include <map>

struct map_charptr
{
    bool operator()(const char* a, const char* b);
};

struct SymbolTable
{
    int depth;
    SymbolTable* parent;
    std::map<char*, int, map_charptr> symbols;
};

extern void pushSymbolTable(SymbolTable*& symbolTable);
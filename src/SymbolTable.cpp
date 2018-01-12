#include <cstddef>
#include <string.h>
#include <map>
#include "SymbolTable.h"

bool map_charptr::operator()(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}

void pushSymbolTable(SymbolTable*& symbolTable)
{
    SymbolTable* childSymbolTable = new SymbolTable();

    if (symbolTable == NULL)
    {
        symbolTable = childSymbolTable;
        symbolTable->depth = 0;
        symbolTable->parent = NULL;
    }
    else
    {
        childSymbolTable->parent = symbolTable;
        symbolTable = childSymbolTable;
        symbolTable->depth = symbolTable->parent->depth + 1;
    }
}

void popSymbolTable(SymbolTable*& symbolTable)
{
    SymbolTable* parent = symbolTable->parent;
    delete symbolTable;
    symbolTable = parent;
}
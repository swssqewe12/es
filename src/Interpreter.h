#pragma once

#include "Node.h"
#include "SymbolTable.h"

class Interpreter
{
    public:
        Interpreter();
        void visit_ProgramTree(ProgramTree* tree);
    private:
        SymbolTable* symbolTable;
        void visit_FuncCallNode(FuncCallNode* node);
        void visit_PrintFuncCallNode(FuncCallNode* node);
        void visit_PrintfFuncCallNode(FuncCallNode* node);
};
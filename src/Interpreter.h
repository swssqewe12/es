#pragma once

#include "Node.h"

class Interpreter
{
    public:
        Interpreter();
        void visit_ProgramTree(ProgramTree* tree);
    private:
        void visit_FuncCallNode(FuncCallNode* node);
};
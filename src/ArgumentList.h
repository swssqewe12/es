#pragma once

struct ArgumentList;

#include "Node.h"

struct ArgumentList
{
    void set(size_t index, Expression arg);
    Expression* get(size_t index);
    size_t size;
};

extern ArgumentList* makeArgumentList(size_t size);
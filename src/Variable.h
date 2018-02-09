#pragma once

enum VariableType
{
    INTEGER
};

struct Variable
{
    __int32 ref_count;
    VariableType type;
    void* value;
};
#pragma once

enum VariableType
{
    INT
};

struct Variable
{
    __int32 ref_count;
    VariableType type;
    void* value;
};
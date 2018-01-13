#include "ArgumentList.h"

void ArgumentList::set(size_t index, Expression arg)
{
    *(Expression*)&((char*) this)[sizeof(size_t) + index * sizeof(Expression)] = arg;
}

Expression* ArgumentList::get(size_t index)
{
    return (Expression*)&((char*) this)[sizeof(size_t) + index * sizeof(Expression)];
}

ArgumentList* makeArgumentList(size_t size)
{
    ArgumentList* args = (ArgumentList*) malloc(sizeof(size_t) + size * sizeof(Expression));
    args->size = size;
    return args;
}
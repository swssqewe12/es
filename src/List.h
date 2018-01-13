#pragma once

#include <cstddef>
#include <cstdlib>

template <class Type>
class List
{
    private:
        int cap = 0;
        Type* arr = NULL;
    public:
        int length;
        int step = 8;

        List()
        {
            this->length = 0;
        }

        List(int length)
        {
            this->length = length;
        }

        Type* push()
        {
            length++;

            if (cap < length)
            {
                cap += step;
                arr = (Type*) realloc(arr, cap * sizeof(Type));
            }

            return get(length - 1);
        }

        void push(Type element)
        {
            *push() = element;
        }

        Type* get(int index)
        {
            return arr + index;
        }

        ~List()
        {
            if (arr)
                free(arr);
        }
};

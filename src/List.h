#pragma once

#include <cstddef>
#include <cstdlib>

template <class Type>
class List
{
    private:
        int cap = 0;
        Type** arr = NULL;
    public:
        int length;
        int step = 10;

        List()
        {
            this->length = 0;
        }

        List(int length)
        {
            this->length = length;
        }

        void push(Type* element)
        {
            length++;

            if (cap < length)
            {
                cap += step;
                arr = (Type**) realloc(arr, cap * sizeof(Type*));
            }

            if (arr)
            {
                arr[length - 1] = element;
            }
        }

        Type* get(int index)
        {
            return arr[index];
        }

        ~List()
        {
            free(arr);
        }
};

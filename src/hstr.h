#pragma once

#include <cstddef>

class hstr
{
    public:
        char* chars;
        size_t step;
        size_t length;

        hstr();
        hstr(const hstr& h_str);
        hstr(char* c_str);
        hstr(char c);
        void append(const hstr& h_str);
        void append(char* c_str);
        void append(char c);
        void shrink_unused();
        char* c_str();
        ~hstr();

    private:
        size_t cap;
};

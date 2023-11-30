#pragma once

// char obj
// int obj
// float obj
// string will be a class in meowlang

#include <cstdint>
#include <string>

enum _const_kind { Int, Float, Char};

struct _const_obj
{
    _const_kind kind;
    union
    {
        struct
        {
            int64_t val; 
        } Integer;

    struct  
        {
            double val;    
        } Float;

        struct
        {
            char *val;
        } Char;

    } data;
};
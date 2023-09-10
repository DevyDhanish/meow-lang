#pragma once

#include <vector>
#include <string>

typedef struct _STRUCT_MEOW_LINE{
    std::string _line;
    size_t line_number;
} meow_line;


std::vector<meow_line> file_to_vect(std::string);
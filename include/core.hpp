#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "token.hpp"

#define START_NODE "__MAIN__"
#define END_NODE "__END__"

// Each prog line get's converted to _STRUCT_MEOW_LINE which helps keep track of which line_number the error occured
typedef struct _STRUCT_MEOW_LINE{
    std::string line;
    size_t line_number;
} meow_line;

// @brief convert file line to meow_line
// @returns vector of meow_line
std::vector<meow_line> file_to_vect(std::string);
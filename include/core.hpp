#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

#include "token.hpp"

extern std::unordered_map<std::string, TOKEN_T> knowTokens;
extern std::unordered_map<char, std::string> operator_pair;
extern std::set<char> brackets;
extern const char commentChar;

// Each prog line get's converted to _STRUCT_MEOW_LINE which helps keep track of which line_number the error occured
typedef struct _STRUCT_MEOW_LINE{
    std::string line;
    size_t line_number;
} meow_line;

// @brief convert file line to meow_line
// @returns vector of meow_line
std::vector<meow_line> file_to_vect(std::string);

std::string format_string(std::string _str);


bool isMeowFile(const std::string& filename);
#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "../token/token.hpp"

#define START_NODE "__MAIN__"
#define END_NODE "__END__"

typedef struct _STRUCT_MEOW_LINE{
    std::string line;
    size_t line_number;
} meow_line;


// class VariableMap{
//     private:
//         std::unordered_map <Token, Token> var_map;
//     public:
//         VariableMap();

//         void add_var(Token key, Token val);
//         Token get_var(Token key);
//         void update_var(Token key, Token val);
// };


std::vector<meow_line> file_to_vect(std::string);
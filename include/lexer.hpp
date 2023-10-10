#pragma once

#include "token.hpp"
#include "core.hpp"

#include <vector>

// Lexer used to convert each word/sentences into tokens
class Lexer{
    private:
        std::vector<Token> _prog_token_list;

    public:
        // @brief the given vector of "meow_line" to a vector of respective tokens
        std::vector<Token> tokenize(meow_line);
};
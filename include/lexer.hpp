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
        void tokenize(std::vector<meow_line>);

        // @breif returns the generated tokens
        std::vector<Token> get_tokenized_vector();
};
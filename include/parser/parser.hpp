#pragma once

#include <vector>
#include "../DS/tree.hpp"
#include "../token/token.hpp"

// Tree _rt_Tree_parse(std::vector<Token> prog_tokens);

class Parser{
    public:
        Tree Parse();
        void Eat();
        void setProg_Tokens(std::vector<Token> prog_tokes);
    private:
        size_t prog_token_counter = 0;
        Token current_token;
        std::vector<Token> meow_prog_tokens;
};
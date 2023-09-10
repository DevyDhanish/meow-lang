#pragma once

#include "../token/token.hpp"
#include "../core/core.hpp"

#include <vector>

class Lexer{
    private:
        std::vector<Token> _prog_token_list;

    public:
        void _rt_None_tokenize(std::vector<meow_line>);
        std::vector<Token> _rt_token_gettokenizedlist();
};
#pragma once

#include "../token/token.hpp"
#include <vector>

class Lexer{
    private:
        std::vector<Token> _prog_token_list;

    public:
        void _rt_None_tokenize(std::vector<std::string>);
        std::vector<Token> _rt_token_gettokenizedlist();
};
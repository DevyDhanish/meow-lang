#pragma once

#include <vector>
#include "tree.hpp"
#include "token.hpp"

// Tree _rt_Tree_parse(std::vector<Token> prog_tokens);

class Parser{
    public:
        // // @brief Feed the parser with the tokenized vector
        // void setToken(std::vector<Token> progTokens){
        //     this->progToken = progTokens;
        // }

        // @parse The tokenized vector `use .setToken()` to give parser the token vector for it to parse
        Tree parse(std::vector<Token>);

    private:
        Token current_token;                    // holds the token the parser is looking at right now
        void advance();                         // sets the current token to the next token
        Tree parseVar();
        Tree parseEqu();
        Tree parseShow();
        Tree parseInt();
        Tree parseStr();
        Tree parseShowStr();
        Tree parseAddSub();
        Tree parseMulDiv();
        Tree parseBee();
        Tree parseMeo();
        Tree parsePika();
        Tree parseAyo();
        Tree parseIf();
        Tree parseEqualsTo();
        std::vector<Token> progToken;           // stores the tokenized vector for the parser to use
        size_t counter = 0;                     // counter to keep track of where it is in the `progToken` token vector
};
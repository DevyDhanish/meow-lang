#pragma once
#include "token.hpp"
#include <vector>
#include <code.hpp>

enum COMPILER_RESULT
{
    COMPILER_ERROR,
    COMPILER_OK,
};

class Compiler
{
private:
    std::vector<Token> tokens;
    std::vector<bytecode> bc;
public:
    uint32_t counter;
    Token prev;
    Token current;
    void advance();
    void fillTokens(const std::vector<Token> &toks) { tokens = toks; advance(); }
    COMPILER_RESULT compile();
    const std::vector<bytecode> &getbytecode() { return bc; }
    void putByte(bytecode byte) { bc.push_back(byte); }
    Compiler() { counter = 0; prev = makeToken(_TOKEN_EMPTY, "none", "none", 0); current = makeToken(_TOKEN_EMPTY, "none", "none", 0); }
};
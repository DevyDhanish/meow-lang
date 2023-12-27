#pragma once

#include "token.hpp"
#include <vector>
#include <cstdint>

// Auditor is just for keeping track of tokens and current tokens no real use tbh.
class Auditor
{
public:
    uint32_t counter;
    std::vector<Token> tokens;
    uint32_t totalSize;

    void meowAudit();

    Auditor(const std::vector<Token> &toks) : tokens(toks) { counter = 0; totalSize = tokens.size(); }

    void move()
    {
        counter++;
    }
};

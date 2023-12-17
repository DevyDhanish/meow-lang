#pragma once

#include <cstdint>
#include <vector>
#include "mewcore_constpool.hpp"

/*
stack
const_pool
*/

class MEOW_STACKFRAME
{
private:
    std::vector<uint64_t> stack;

public:
    std::vector<const_pair *> pool;
    uint16_t stack_pointer;
    void pushToStack(uint64_t val);
    uint64_t popFromStack();
    void replaceValInStack(uint16_t idx, uint64_t val);
    uint64_t getValFromStack(uint16_t idx);

    MEOW_STACKFRAME()
    {
        stack_pointer = 0;
    }
};
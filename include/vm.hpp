#pragma once

#include <vector>
#include "internals/mewcore_stackframe.hpp"
#include "code.hpp"
#include "byteblocks.hpp"
#include <stack>

/*
frame
*/

class Interpreter
{
private:
    std::stack<MEOW_STACKFRAME *> frame;

public:
    uint32_t recursion_limit;
    uint32_t recursion;
    Block *code;
    //Block *currExecBlock;

    Interpreter(Block *c) : code(c)
    {
        recursion_limit = 3000;
    }

    void Execute();
};

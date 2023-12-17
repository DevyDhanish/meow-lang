#pragma once

#include <vector>
#include "internals/mewcore_stackframe.hpp"
#include "code.hpp"
#include "byteblocks.hpp"

/*
frame
*/

class Interpreter
{
private:
    std::vector<MEOW_STACKFRAME *> frame;
    Block *cooked_code;
public:
    int64_t ip;
    MEOW_STACKFRAME *current_frame;
    Block *currExecBlock;

    void pushFrame(MEOW_STACKFRAME *f);
    void popFrame();

    void jumpIpForward(uint32_t offset);
    void jumpIpBackward(uint32_t offset);

    Interpreter(Block *cc) : cooked_code(cc)
    {
        ip = 0;
    }

    void Execute(std::string _id, MEOW_STACKFRAME *frame);
};

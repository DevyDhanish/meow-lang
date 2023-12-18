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
    int64_t ip_state;
    MEOW_STACKFRAME *current_frame;
    Block *currExecBlock;
    Block *block_state;

    void pushFrame(MEOW_STACKFRAME *f);
    void popFrame();

    void jumpIpForward(uint32_t offset);
    void jumpIpBackward(uint32_t offset);

    void saveip();
    void loadip();

    void saveblock();
    void loadblock();

    Interpreter(Block *cc) : cooked_code(cc)
    {
        ip = 0;
    }

    void Execute(std::string _id, MEOW_STACKFRAME *frame);
};

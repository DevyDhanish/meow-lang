#pragma once

#include <vector>

#include "internals/mewcore_stackframe.hpp"
#include "code.hpp"

class PROG_FRAME
{
    public: 
    std::vector<MEOW_STACKFRAME *> frame;
    uint32_t frame_pointer;

    // push frame
    void push_frame(MEOW_STACKFRAME *f);
    // pop frame
    void pop_frame();

    PROG_FRAME()
    {
        frame_pointer = 0;
    }
};

void startexec(const std::vector<bytecode> cooked_code);
#pragma once

#include <vector>
#include "internals/mewcore_stackframe.hpp"
#include "code.hpp"

/*
frame
*/

class Interpreter
{
private:
    std::vector<MEOW_STACKFRAME *> frame;
public:
    uint16_t fp;
    MEOW_STACKFRAME *current_frame;

    void pushFrame(MEOW_STACKFRAME *f);
    MEOW_STACKFRAME *popFrame();

    Interpreter()
    {
        fp = 0;
    }
};

void startexec(const std::vector<bytecode> &cooked_code);
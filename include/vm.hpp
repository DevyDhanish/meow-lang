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
    int64_t ip;
    const std::vector<bytecode> &cooked_code;
public:
    bool isFinished;
    uint16_t fp;
    MEOW_STACKFRAME *current_frame;

    void pushFrame(MEOW_STACKFRAME *f);
    MEOW_STACKFRAME *popFrame();

    void jumpIpForward(uint32_t offset);
    void jumpIpBackward(uint32_t offset);
    void moveForward();
    bytecode getByteAtIp();

    Interpreter(const std::vector<bytecode> &cc) : cooked_code(cc)
    {
        fp = 0;
        ip = 0;
        isFinished = false;
    }
};

void startexec(const std::vector<bytecode> &cooked_code);
#pragma once

#include <cstdint>
#include <vector>
#include "mewcore_constpool.hpp"
#include "../byteblocks.hpp"

/*
stack
const_pool
*/

enum FRAME_EXIT_CODE
{
    FRAME_EXIT_NORMAL,
    FRAME_CALL,
    FRAME_RETURN,
};

class MEOW_STACKFRAME
{
private:
    std::vector<uint64_t> stack;
    uint32_t ip;
    uint32_t ip_savepoint;
    Block *code;

public:
    std::vector<const_pair *> *pool;
    uint16_t stack_pointer;
    void pushToStack(uint64_t val);
    uint64_t popFromStack();
    // void replaceValInStack(uint16_t idx, uint64_t val);
    // uint64_t getValFromStack(uint16_t idx);

    bytecode getByteByIp();

    void incrementip(uint32_t offset);
    void decrementip(uint32_t offset);

    FRAME_EXIT_CODE executeFrame();
    FRAME_EXIT_CODE resumeFrame();

    MEOW_STACKFRAME(Block *_code) : code(_code)
    {
        ip = 0;
        pool = new std::vector<const_pair *>;
    }
};
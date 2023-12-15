#include "../../include/code.hpp"

bytecode makeByteCode(uint8_t op, uint64_t oparg)
{
    bytecode bc;
    bc.op = op;
    bc.arg = oparg;

    return bc;
}
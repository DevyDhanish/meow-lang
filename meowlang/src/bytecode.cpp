#include "../../include/code.hpp"
#include <vector>
#include <string>

bytecode makeByteCode(uint8_t op, uint64_t oparg)
{
    bytecode bc;
    bc.op = op;
    bc.arg = oparg;

    return bc;
}

std::vector<std::string> opcodes_string
{
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "STORE",
    "LOAD_NAME",
    "LOAD_CONST",
    "MAKE_FUNC",
    "MAKE_CLASS",
    "OUT",
    "CMP_EQU",
    "CMP_NOTEQU",
    "CMP_LESS",
    "CMP_LESSEQU",
    "CMP_GREAT",
    "CMP_GREATEQU",
    "NEGATE",
    "AND",
    "OR",
    "NOT",
    "JUMP",
    "JUMP_BACK",
    "JUMP_IF_FALSE",
    "CALL",
    "RETURN",
    "IDX",
    "SET_IDX",
    "FOR_ITER",
    "GET_NEXT",
};
#pragma once
#include <stdint.h>

typedef struct _CODE_UINT bytecode; 

enum OP_CODES
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    STORE,
    LOAD_CONST,
    MAKE_FUNC,
    MAKE_CLASS,
    OUT,
};
struct _CODE_UINT
{
    uint8_t op;
    int64_t arg;
};

bytecode makeByteCode(uint8_t op, int64_t oparg);

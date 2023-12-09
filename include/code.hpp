#include <stdint.h>

typedef struct _CODE_UINT bytecode; 

enum OP_CODES
{
    ADD,
    MUL,
    DIV,
    MOD,
    STORE,
    LOAD_CONST,
    MAKE_FUNC,
    MAKE_CLASS,
};
    
struct _CODE_UINT
{
    uint8_t op;
    int64_t arg;
};

bytecode makeBytecode(uint8_t _op, int64_t oparg)
{
    bytecode bc;
    bc.op = _op;
    bc.arg = oparg;

    return bc;
}
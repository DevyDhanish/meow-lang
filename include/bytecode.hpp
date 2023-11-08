#pragma once

#include "token.hpp"

typedef enum _Meow_byte_code
{
    PUSH,           // push something to the stack
    POP,            // pop something from the stack
    ADD,            // addition 
    MUL,            // multiply
    SUB,            // substract
    DIV,            // divide
    MOD,            // modulus
    STORE,          // store a value in a variable
} bytecode_type;

typedef struct
{
    bytecode_type mnemonic;
    Token operand;             // some mnemonic like cmp don't need a operand that's why operand is a pointer so that when used with logical mnemonic the operand can be set to nullptr
} bytecode;


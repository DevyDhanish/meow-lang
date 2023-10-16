#pragma once

#include "token.hpp"
#include <vector>
#include <unordered_map>

typedef enum _MEOW_BYTE_CODE{

    _OP_OUT,                // 0    SHOW
    _OP_LOOP,               // 1    FOR LOOPS AND WHILE LOOPS
    _OP_CMP_EQU,            // 2    X == X
    _OP_CMP_LESS,           // 3    X <  X
    _OP_CMP_GREATER,        // 4    X >  X
    _OP_CMP_NOTEQU,         // 5    X != X
    _OP_SET,                // 6    X = SOMETHING
    _OP_ELSE,               // 7    else

} MEOW_BYTE_CODE;


typedef struct _STRUCT_MEOW_BYTE_CODE{
    MEOW_BYTE_CODE mnemonic;
    Token operand_1;
    Token operand_2;
} Byte_code;

extern std::vector<Byte_code> meow_byte_code;
extern std::unordered_map<Token, Token> global_variable_map;

Byte_code makeByteCode(MEOW_BYTE_CODE _mnemonic, Token _op1, Token _op2);
void run();
void submitByteCode(Byte_code b_c);
void showByteCode();
void runByteCode(Byte_code &curr_bc, size_t &counter);
void runIfBlock(size_t &counter);
void runElseBlock(size_t &counter);
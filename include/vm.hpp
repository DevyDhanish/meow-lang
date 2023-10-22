#pragma once

#include "token.hpp"
#include "tree.hpp"
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
    _OP_CMP_LESSEQU,        // 8    x <= x
    _OP_CMP_GREAEQU,        // 9    x >= x
    _OP_ENDIF,              // 10
    _OP_ENDELSE,            // 11
    _OP_IN,                 // 12
    _OP_EXIT,               // 13
    _OP_ENDWHILE,           // 14

} MEOW_BYTE_CODE;

typedef struct _STRUCT_MEOW_BYTE_CODE{
    MEOW_BYTE_CODE mnemonic;
    Tree operand_1;
    Tree operand_2;
} Byte_code;

extern std::vector<Byte_code> meow_byte_code;
extern std::unordered_map<Token, Token> global_variable_map;
extern size_t instruction_pointer;
extern Byte_code current_instruction;

Byte_code makeByteCode(MEOW_BYTE_CODE _mnemonic, Tree _op1, Tree _op2);
void run();
void submitByteCode(Byte_code b_c);
void showByteCode();
void runByteCode();
void runIfBlock();
void runElseBlock();
void runLoopBlock();
void advance();
void goback();
bool isOperator(Token op);
//void preproces();
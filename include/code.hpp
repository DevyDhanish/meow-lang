#pragma once
#include <stdint.h>

typedef struct _CODE_UINT bytecode; 

enum OP_CODES
{
    ADD,    //0
    SUB,    //1
    MUL,    //2
    DIV,    //3
    MOD,    //4
    STORE,  //5
    LOAD_NAME,  //6
    LOAD_CONST, //7
    MAKE_FUNC,  //8
    MAKE_CLASS, //9
    OUT,    //10
    CMP_EQU, // 11
    CMP_NOTEQU,        // 12
    CMP_LESS,        //13
    CMP_LESSEQU,    //14
    CMP_GREAT,      //15
    CMP_GREATEQU,   //16
    NEGATE,         // 17
    AND,            // 18
    OR,             // 19
    NOT,            // 20
    JUMP,           // 21
    JUMP_IF_TRUE,   // 22
    JUMP_IF_FALSE,  // 23
};
struct _CODE_UINT
{
    uint8_t op;
    uint64_t arg;
};

bytecode makeByteCode(uint8_t op, uint64_t oparg);

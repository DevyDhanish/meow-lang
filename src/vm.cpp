#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"
#include "../include/map.hpp"
#include "../include/error.hpp"
#include <assert.h>
#include <ctype.h>
#include <string>
#include <cmath>
#include <ctype.h>

std::vector<Byte_code> meow_byte_code;
size_t instruction_pointer = 0;
Byte_code current_instruction;

void advance(){
    if(instruction_pointer < meow_byte_code.size()){
        current_instruction = meow_byte_code[instruction_pointer];
        instruction_pointer++;
    }
    else
    {
        current_instruction = makeByteCode(_OP_EXIT,
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)),
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)));
    }
}

void goback(){
    if(instruction_pointer > 0){
        instruction_pointer--;
        current_instruction = meow_byte_code[instruction_pointer];
    }
    else
    {
        current_instruction = makeByteCode(_OP_EXIT,
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)),
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)));
    }
}

Byte_code makeByteCode(MEOW_BYTE_CODE _mnemonic, Tree _op1, Tree _op2){
    Byte_code newByteCode;
    newByteCode.mnemonic = _mnemonic;
    newByteCode.operand_1 = _op1;
    newByteCode.operand_2 = _op2;
    return newByteCode;
}

void submitByteCode(Byte_code b_c){
    meow_byte_code.push_back(b_c);
}

void showByteCode(){
    std::unordered_map<_MEOW_BYTE_CODE, std::string> byte_code_table = {
        {_OP_OUT, "_OP_OUT"},
        {_OP_LOOP, "_OP_LOOP"},
        {_OP_CMP_EQU, "_OP_CMP_EQU"},
        {_OP_CMP_LESS, "_OP_CMP_LESS"},
        {_OP_CMP_GREATER,"_OP_CMP_GREATER"},
        {_OP_CMP_NOTEQU,"_OP_CMP_NOTEQU"},
        {_OP_SET,"_OP_SET"},
        {_OP_ELSE,"_OP_ELSE"},
        {_OP_CMP_LESSEQU,"_OP_CMP_LESSEQU"},
        {_OP_CMP_GREAEQU,"_OP_CMP_GREAEQU"},
        {_OP_ENDIF,"_OP_ENDIF"},
        {_OP_ENDELSE,"_OP_ENDELSE"},
        {_OP_IN,"_OP_IN"},
        {_OP_EXIT,"_OP_EXIT"},
        {_OP_ENDWHILE,"_OP_ENDWHILE"},
    };
    int count = 1;
    for(Byte_code i : meow_byte_code){
        std::cout << count << " : " << byte_code_table[i.mnemonic] << " " << i.operand_1.data._TOKEN_VALUE << " " << i.operand_2.data._TOKEN_VALUE << "\n";
        count++;
    }
}
#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"

std::vector<Byte_code> meow_byte_code;

Byte_code makeByteCode(MEOW_BYTE_CODE _mnemonic, Token _op1, Token _op2){
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
    for(Byte_code i : meow_byte_code){
        std::cout << " " << i.mnemonic << " " << i.operand_1._TOKEN_VALUE << " " << i.operand_2._TOKEN_VALUE << "\n";
    }
}

void run(){
    for(Byte_code i : meow_byte_code){
        if(i.mnemonic == _OP_SET){
            insert(i.operand_1, i.operand_2);
        }

        else if(i.mnemonic == _OP_OUT){
            if(i.operand_1._TOKEN_TYPE == _TOKEN_VAR){
                Token var = get(i.operand_1);
                std::cout << format_string(var._TOKEN_VALUE);
            }
            else{
                std::cout << format_string(i.operand_1._TOKEN_VALUE);
            }
        }
    }
}
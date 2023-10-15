#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"
#include <assert.h>

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

bool compareTokens(TOKEN_T token_type, MEOW_BYTE_CODE cmp_type, Token left_op, Token right_op){
    if(cmp_type == _OP_CMP_EQU){
        //std::cout << "LJLDJF" << left_op._TOKEN_TYPE;
        if(token_type == _TOKEN_INT){
            return (std::stold(left_op._TOKEN_VALUE) == std::stold(right_op._TOKEN_VALUE));
        }
    }

    return false;
}

void jumpToElse(size_t &counter){
    while(counter < meow_byte_code.size()){
        Byte_code curr_bc = meow_byte_code[counter];

        if(curr_bc.mnemonic == _OP_ELSE){
            return;
        }

        counter++;
    }
}

void run(){
    size_t counter = 0;

    while(counter < meow_byte_code.size()){
        Byte_code curr_bc = meow_byte_code[counter];

        if(curr_bc.mnemonic == _OP_SET){
            insert(curr_bc.operand_1, curr_bc.operand_2);
        }

        else if(curr_bc.mnemonic == _OP_OUT){
            if(curr_bc.operand_1._TOKEN_TYPE == _TOKEN_VAR){
                Token var = get(curr_bc.operand_1);
                std::cout << format_string(var._TOKEN_VALUE);
            }
            else{
                std::cout << format_string(curr_bc.operand_1._TOKEN_VALUE);
            }
        }

        else if(curr_bc.mnemonic == _OP_CMP_EQU){
            if(!compareTokens(curr_bc.operand_1._TOKEN_TYPE, _OP_CMP_EQU, curr_bc.operand_1, curr_bc.operand_2)){
                jumpToElse(counter);
            }
        }

        counter++;
    }
}
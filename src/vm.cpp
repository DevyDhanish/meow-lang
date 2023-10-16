#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"
#include "../include/map.hpp"
#include <assert.h>

std::vector<Byte_code> meow_byte_code;
int LAST_LOGIC_FLAG = 1;

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

        if(token_type == _TOKEN_VAR){
            Token l_op = get(left_op);
            Token r_op = get(right_op);

            if(l_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_INT){
                return (std::stold(l_op._TOKEN_VALUE) == std::stold(right_op._TOKEN_VALUE));
            }

            if(token_type == _TOKEN_STRING){
                return (left_op._TOKEN_VALUE == right_op._TOKEN_VALUE);
            }
        }

        if(token_type == _TOKEN_STRING){
            return (left_op._TOKEN_VALUE == right_op._TOKEN_VALUE);
        }
    }

    if(cmp_type == _OP_CMP_LESS){
        //std::cout << "LJLDJF" << left_op._TOKEN_TYPE;
        if(token_type == _TOKEN_INT){
            return (std::stold(left_op._TOKEN_VALUE) < std::stold(right_op._TOKEN_VALUE));
        }

        if(token_type == _TOKEN_VAR){
            Token l_op = get(left_op);
            Token r_op = get(right_op);

            if(l_op._TOKEN_TYPE == _TOKEN_INT && r_op._TOKEN_TYPE == _TOKEN_INT){
                return (std::stold(l_op._TOKEN_VALUE) < std::stold(r_op._TOKEN_VALUE));
            }

        }
    }

    if(cmp_type == _OP_CMP_GREATER){
        //std::cout << "LJLDJF" << left_op._TOKEN_TYPE;
        if(token_type == _TOKEN_INT){
            return (std::stold(left_op._TOKEN_VALUE) > std::stold(right_op._TOKEN_VALUE));
        }
        if(token_type == _TOKEN_VAR){
            Token l_op = get(left_op);
            Token r_op = get(right_op);

            if(l_op._TOKEN_TYPE == _TOKEN_INT && r_op._TOKEN_TYPE == _TOKEN_INT){
                return (std::stold(l_op._TOKEN_VALUE) > std::stold(r_op._TOKEN_VALUE));
            }
        }
    }

    if(cmp_type == _OP_CMP_NOTEQU){
        //std::cout << "LJLDJF" << left_op._TOKEN_TYPE;
        if(token_type == _TOKEN_INT){
            return (std::stold(left_op._TOKEN_VALUE) != std::stold(right_op._TOKEN_VALUE));
        }
        if(token_type == _TOKEN_VAR){
            Token l_op = get(left_op);
            Token r_op = get(right_op);

            if(l_op._TOKEN_TYPE == _TOKEN_INT && r_op._TOKEN_TYPE == _TOKEN_INT){
                return (std::stold(l_op._TOKEN_VALUE) != std::stold(r_op._TOKEN_VALUE));
            }

            if(token_type == _TOKEN_STRING){
                return (left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
            }
        }

        if(token_type == _TOKEN_STRING){
            return (left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
        }
    }

    if(cmp_type == _OP_CMP_LESSEQU){
        //std::cout << "LJLDJF" << left_op._TOKEN_TYPE;
        if(token_type == _TOKEN_INT){
            return (std::stold(left_op._TOKEN_VALUE) <= std::stold(right_op._TOKEN_VALUE));
        }
        if(token_type == _TOKEN_VAR){
            Token l_op = get(left_op);
            Token r_op = get(right_op);

            if(l_op._TOKEN_TYPE == _TOKEN_INT && r_op._TOKEN_TYPE == _TOKEN_INT){
                return (std::stold(l_op._TOKEN_VALUE) <= std::stold(r_op._TOKEN_VALUE));
            }
        }
    }

    if(cmp_type == _OP_CMP_GREAEQU){
        //std::cout << "LJLDJF" << left_op._TOKEN_TYPE;
        if(token_type == _TOKEN_INT){
            return (std::stold(left_op._TOKEN_VALUE) >= std::stold(right_op._TOKEN_VALUE));
        }

        if(token_type == _TOKEN_VAR){
            Token l_op = get(left_op);
            Token r_op = get(right_op);

            if(l_op._TOKEN_TYPE == _TOKEN_INT && r_op._TOKEN_TYPE == _TOKEN_INT){
                return (std::stold(l_op._TOKEN_VALUE) >= std::stold(r_op._TOKEN_VALUE));
            }

        }

    }

    return false;
}

void runIfBlock(size_t &counter){
    Byte_code curr_bc = meow_byte_code[counter];
    int if_indent = curr_bc.operand_1._INDENTATION;

    counter++;
    curr_bc = meow_byte_code[counter];
    int curr_idt = curr_bc.operand_1._INDENTATION;
    while(curr_bc.operand_1._INDENTATION == curr_idt)
    {

        runByteCode(curr_bc, counter);

        counter++;
        curr_bc = meow_byte_code[counter];

    }

    if(curr_bc.mnemonic == _OP_ELSE && curr_bc.operand_1._INDENTATION == if_indent){
        counter++;
        curr_bc = meow_byte_code[counter];
        while(curr_bc.operand_1._INDENTATION != if_indent){
            counter++;
            curr_bc = meow_byte_code[counter];
        }
    }

    counter--;
}

void runElseBlock(size_t &counter){
    Byte_code curr_bc = meow_byte_code[counter];

    while(curr_bc.mnemonic != _OP_ELSE){
        //std::cout << curr_bc.operand_1._TOKEN_LINE;
        counter++;
        curr_bc = meow_byte_code[counter];
    }     // leave us at else:

    counter++;
    curr_bc = meow_byte_code[counter];
    int curr_idt = curr_bc.operand_1._INDENTATION;

    while(curr_bc.operand_1._INDENTATION == curr_idt)
    {

        runByteCode(curr_bc, counter);

        counter++;
        curr_bc = meow_byte_code[counter];
    }

    counter--;
}

void runByteCode(Byte_code &curr_bc, size_t &counter){
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
    else if(curr_bc.mnemonic == _OP_CMP_EQU ||
            curr_bc.mnemonic == _OP_CMP_LESS ||
            curr_bc.mnemonic == _OP_CMP_GREATER ||
            curr_bc.mnemonic == _OP_CMP_NOTEQU  ||
            curr_bc.mnemonic == _OP_CMP_LESSEQU  ||
            curr_bc.mnemonic == _OP_CMP_GREAEQU
        ){

        if(compareTokens(curr_bc.operand_1._TOKEN_TYPE, curr_bc.mnemonic, curr_bc.operand_1, curr_bc.operand_2))
        {
            runIfBlock(counter);
        }
        else
        {
            runElseBlock(counter);
        }
    }
}

void run(){
    size_t counter = 0;

    while(counter < meow_byte_code.size()){
        Byte_code curr_bc = meow_byte_code[counter];
        
        runByteCode(curr_bc, counter);

        counter++;
    }
}
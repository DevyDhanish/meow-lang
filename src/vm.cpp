#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"
#include "../include/map.hpp"
#include <assert.h>

std::vector<Byte_code> meow_byte_code;
size_t instruction_pointer = 0;
Byte_code current_instruction;

void advance(){
    if(instruction_pointer < meow_byte_code.size()){
        instruction_pointer++;
        current_instruction = meow_byte_code[instruction_pointer];
    }
}

void goback(){
    if(instruction_pointer > 0){
        instruction_pointer--;
        current_instruction = meow_byte_code[instruction_pointer];
    }
}

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

bool compareEquals(Token left_op, Token right_op)
{
    if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    {
        return(left_op._TOKEN_VALUE == right_op._TOKEN_VALUE);
    }
    else if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        std::cout << "Cannot `==` between a string and a int\n";
        return 0;
    }
    else
    {
        return(std::stold(left_op._TOKEN_VALUE) == std::stold(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareNotEquals(Token left_op, Token right_op)
{
    if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    {
        return(left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
    }
    else if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        std::cout << "Cannot `!=` between a string and a int\n";
        return 0;
    }
    else
    {
        return(std::stold(left_op._TOKEN_VALUE) != std::stold(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareLessEquals(Token left_op, Token right_op)
{
    // if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    // {
    //     return(left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
    // }
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        std::cout << "Cannot `<=` between a string and a int\n";
        return 0;
    }
    else
    {
        return(std::stold(left_op._TOKEN_VALUE) <= std::stold(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareGreaterEquals(Token left_op, Token right_op)
{
    // if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    // {
    //     return(left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
    // }
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        std::cout << "Cannot `>=` between a string and a int\n";
        return 0;
    }
    else
    {
        return(std::stold(left_op._TOKEN_VALUE) >= std::stold(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareLess(Token left_op, Token right_op)
{
    // if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    // {
    //     return(left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
    // }
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        std::cout << "Cannot `<` between a string and a int\n";
        return 0;
    }
    else
    {
        return(std::stold(left_op._TOKEN_VALUE) < std::stold(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareGreater(Token left_op, Token right_op)
{
    // if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    // {
    //     return(left_op._TOKEN_VALUE != right_op._TOKEN_VALUE);
    // }
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        std::cout << "Cannot `>` between a string and a int\n";
        return 0;
    }
    else
    {
        return(std::stold(left_op._TOKEN_VALUE) > std::stold(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareTokens(MEOW_BYTE_CODE cmp_type, Token left_op, Token right_op){

    typedef bool (*compareFunctionPtr)(Token, Token);

    compareFunctionPtr cmpfncptr;

    switch(cmp_type){
        case _OP_CMP_EQU:
            cmpfncptr = &compareEquals;
            break;
        case _OP_CMP_NOTEQU:
            cmpfncptr = &compareNotEquals;
            break;
        case _OP_CMP_LESSEQU:
            cmpfncptr = &compareLessEquals;
            break;
        case _OP_CMP_GREAEQU:
            cmpfncptr = &compareGreaterEquals;
            break;
        case _OP_CMP_LESS:
            cmpfncptr = &compareLess;
            break;
        case _OP_CMP_GREATER:
            cmpfncptr = &compareGreater;
            break;
        default:
            cmpfncptr = &compareEquals;
    }

    if(left_op._TOKEN_TYPE == _TOKEN_VAR && right_op._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token l_var = get(left_op);
        Token r_var = get(right_op);

        return (*cmpfncptr)(l_var, r_var);
    }

    else if(left_op._TOKEN_TYPE == _TOKEN_VAR && right_op._TOKEN_TYPE != _TOKEN_VAR)
    {
        Token l_var = get(left_op);

        return (*cmpfncptr)(l_var, right_op);
    }

    else if(left_op._TOKEN_TYPE != _TOKEN_VAR && right_op._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token r_var = get(right_op);

        return (*cmpfncptr)(left_op, r_var);
    }

    else
    {
        return (*cmpfncptr)(left_op, right_op);
    }
}

void runIfBlock()
{
    int curr_if_indent = current_instruction.operand_1._INDENTATION;
    advance();
    while (1)
    {
        if(current_instruction.mnemonic == _OP_ENDIF && 
        current_instruction.operand_1._INDENTATION == curr_if_indent) break;

        runByteCode();
        advance();
    }

    advance();

    if(current_instruction.mnemonic == _OP_ELSE)
    {
        //int curr_else_indent = current_instruction.operand_1._INDENTATION;
        advance();
        while(1)
        {
            if(current_instruction.mnemonic == _OP_ENDELSE &&
            current_instruction.operand_1._INDENTATION == curr_if_indent) break;

            advance();
        };
        
    }

}

void runElseBlock()
{
    int curr_if_indent = current_instruction.operand_1._INDENTATION;
    advance();
    while(1)
    {
        if(current_instruction.mnemonic == _OP_ENDIF && 
        current_instruction.operand_1._INDENTATION == curr_if_indent) break;

        advance();
    }

    advance();

    if(current_instruction.mnemonic == _OP_ELSE)
    {
        int curr_else_indent = current_instruction.operand_1._INDENTATION;
        advance();

        while(1)
        {
            if(current_instruction.mnemonic == _OP_ENDELSE &&
                current_instruction.operand_1._INDENTATION == curr_else_indent) break;

            runByteCode();
            advance();
        }
    }
}

void runByteCode(){
    if(current_instruction.mnemonic == _OP_SET){
        insert(current_instruction.operand_1, current_instruction.operand_2);
    }
    else if(current_instruction.mnemonic == _OP_OUT){
        if(current_instruction.operand_1._TOKEN_TYPE == _TOKEN_VAR){
            Token var = get(current_instruction.operand_1);
            std::cout << format_string(var._TOKEN_VALUE) << "\n";
        }
        else{
            std::cout << format_string(current_instruction.operand_1._TOKEN_VALUE) << "\n";
        }
    }

    else if(current_instruction.mnemonic == _OP_CMP_EQU ||
            current_instruction.mnemonic == _OP_CMP_LESS ||
            current_instruction.mnemonic == _OP_CMP_GREATER ||
            current_instruction.mnemonic == _OP_CMP_NOTEQU  ||
            current_instruction.mnemonic == _OP_CMP_LESSEQU  ||
            current_instruction.mnemonic == _OP_CMP_GREAEQU
        ){

        if(compareTokens(current_instruction.mnemonic, current_instruction.operand_1, current_instruction.operand_2))
        {
            runIfBlock();
        }
        else
        {
            runElseBlock();
        }
    }
}

void run()
{
    current_instruction = meow_byte_code[instruction_pointer];
    while(instruction_pointer < meow_byte_code.size())
    {
        runByteCode();

        advance();
    }
}
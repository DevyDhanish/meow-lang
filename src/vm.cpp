#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"
#include "../include/map.hpp"
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

bool compareTokens(TOKEN_T token_type, MEOW_BYTE_CODE cmp_type, Token left_op, Token right_op){

    typedef bool (*compareFunctionPtr)(Token, Token);

    compareFunctionPtr cmpfncptr;

    // bool (*cmpEquals)(Token, Token) = &compareEquals;
    // bool (*cmpNotEquals)(Token, Token) = &compareNotEquals;
    // bool (*cmpLessEquals)(Token, Token) = &compareLessEquals;
    // bool (*cmpGreaterEquals)(Token, Token) = &compareGreaterEquals;
    // bool (*cmpLess)(Token, Token) = &compareLess;
    // bool (*cmpGreater)(Token, Token) = &compareGreater;

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

        counter--;
    }

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

void runLoopBlock(size_t &counter){
    Byte_code curr_bc = meow_byte_code[counter];
    int limit = std::stold(curr_bc.operand_1._TOKEN_VALUE);

    counter++;
    size_t save_ctr = counter;

    curr_bc = meow_byte_code[counter];
    int curr_idt = curr_bc.operand_1._INDENTATION;
    int c = 1;

    while(c < limit){
        while(curr_bc.operand_1._INDENTATION == curr_idt)
        {

            runByteCode(curr_bc, counter);

            counter++;
            curr_bc = meow_byte_code[counter];

        }
        c++;
        counter = save_ctr;
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
            std::cout << format_string(var._TOKEN_VALUE) << "\n";
        }
        else{
            std::cout << format_string(curr_bc.operand_1._TOKEN_VALUE) << "\n";
        }
    }

    else if(curr_bc.mnemonic == _OP_LOOP){
        runLoopBlock(counter);
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
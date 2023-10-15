#include "../include/interpreter.hpp"
#include "../include/token.hpp"
#include "../include/vm.hpp"
#include <unordered_map>
#include <iostream>
#include <string>
#include <assert.h>

std::unordered_map<TOKEN_T, MEOW_BYTE_CODE> token_byte_code_relation{
    {_TOKEN_EQU, _OP_SET},
    {_TOKEN_SHOW, _OP_OUT},
};

void createAndSubmitByteCode(Token oper, Token oper1, Token oper2){
    submitByteCode(
        makeByteCode(
            token_byte_code_relation[oper._TOKEN_TYPE],
            oper1,
            oper2
        )
    );
}

long double solveExpression(Tree root){
    Tree child_tok = root;
    
    if(child_tok.data._TOKEN_TYPE == _TOKEN_PLUS){
        return solveExpression(root.get_child(0)) + solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MUL){
        return solveExpression(root.get_child(0)) * solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MINUS){
        return solveExpression(root.get_child(0)) - solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_DIV){
        return solveExpression(root.get_child(0)) / solveExpression(root.get_child(1));
    }
    else{
        return std::stold(child_tok.data._TOKEN_VALUE);
    }
}

void Interpreter::generateAssignmentByteCode(Token op, Tree op1, Tree op2) {

    if(op2.data._TOKEN_TYPE == _TOKEN_PLUS      ||
        op2.data._TOKEN_TYPE == _TOKEN_MINUS    ||
        op2.data._TOKEN_TYPE == _TOKEN_MUL      ||
        op2.data._TOKEN_TYPE == _TOKEN_DIV      ||
        op2.data._TOKEN_TYPE == _TOKEN_MOD
        ){

        op2.data._TOKEN_VALUE = std::to_string(solveExpression(op2));
    }

    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateShowByteCode(Token op, Tree op1){

    if(op1.data._TOKEN_TYPE == _TOKEN_PLUS      ||
        op1.data._TOKEN_TYPE == _TOKEN_MINUS    ||
        op1.data._TOKEN_TYPE == _TOKEN_MUL      ||
        op1.data._TOKEN_TYPE == _TOKEN_DIV      ||
        op1.data._TOKEN_TYPE == _TOKEN_MOD
        ){

        op1.data._TOKEN_VALUE = std::to_string(solveExpression(op1));
    }

    Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::convertToByteCode(Tree root) {

    if(root.data._TOKEN_TYPE == _TOKEN_VAR){
        Tree op1 = root;
        Tree optr = op1.get_child(0);
        if(optr.data._TOKEN_TYPE == _TOKEN_EQU){
            Tree op2 = optr.get_child(0); 
            generateAssignmentByteCode(optr.data, op1, op2);
        }
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_SHOW){

        generateShowByteCode(root.data, root.get_child(0));
    }
}
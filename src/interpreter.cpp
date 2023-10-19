#include "../include/interpreter.hpp"
#include "../include/token.hpp"
#include "../include/vm.hpp"
#include "../include/map.hpp"
#include <unordered_map>
#include <iostream>
#include <string>
#include <assert.h>

std::unordered_map<TOKEN_T, MEOW_BYTE_CODE> token_byte_code_relation{
    {_TOKEN_EQU, _OP_SET},
    {_TOKEN_SHOW, _OP_OUT},
    {_TOKEN_EQUALSTO, _OP_CMP_EQU},
    {_TOKEN_LESSTHAN, _OP_CMP_LESS},
    {_TOKEN_LESSEQU, _OP_CMP_LESSEQU},
    {_TOKEN_GREATEREQU, _OP_CMP_GREAEQU},
    {_TOKEN_GREATERTHAN, _OP_CMP_GREATER},
    {_TOKEN_NOTEQUALS, _OP_CMP_NOTEQU},
    {_TOKEN_ELSE, _OP_ELSE},
    {_TOKEN_WHILE, _OP_LOOP}
};

std::unordered_map<std::string, long double> symbolTable;

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
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_VAR)
    {
        return symbolTable[root.data._TOKEN_VALUE];
    }
    else
    {
        return std::stold(child_tok.data._TOKEN_VALUE);
    }
}

void createAndSubmitByteCode(Token oper, Token oper1, Token oper2){
    submitByteCode(
        makeByteCode(
            token_byte_code_relation[oper._TOKEN_TYPE],
            oper1,
            oper2
        )
    );
}

void solveExpressionAndAssignValue(Tree &op, long double val){
    if( op.data._TOKEN_TYPE  == _TOKEN_PLUS    ||
        op.data._TOKEN_TYPE == _TOKEN_MINUS    ||
        op.data._TOKEN_TYPE == _TOKEN_MUL      ||
        op.data._TOKEN_TYPE == _TOKEN_DIV      ||
        op.data._TOKEN_TYPE == _TOKEN_MOD
        ){
            // op.data._TOKEN_VALUE = std::to_string(solveExpression(op));
            // op.data._TOKEN_TYPE == _TOKEN_INT;

            op.data = makeToken(
                _TOKEN_INT,
                std::to_string(val),
                op.data._TOKEN_LINE,
                op.data._TOKEN_LINE_NUMBER,
                op.data._INDENTATION
            );
    }
}


void Interpreter::generateAssignmentByteCode(Token op, Tree op1, Tree op2) {

    if(op2.data._TOKEN_TYPE == _TOKEN_INT ||
        op2.data._TOKEN_TYPE == _TOKEN_PLUS ||
        op2.data._TOKEN_TYPE == _TOKEN_MINUS ||
        op2.data._TOKEN_TYPE == _TOKEN_MUL ||
        op2.data._TOKEN_TYPE == _TOKEN_DIV
        )
    {
        symbolTable[op1.data._TOKEN_VALUE] = solveExpression(op2);
        solveExpressionAndAssignValue(op2, symbolTable[op1.data._TOKEN_VALUE]);
    }

    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateShowByteCode(Token op, Tree op1){

    if(op1.data._TOKEN_TYPE == _TOKEN_INT) solveExpressionAndAssignValue(op1, solveExpression(op1));

    Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateIfByteCode(Token op, Tree op1, Tree op2){

    if(op1.data._TOKEN_TYPE == _TOKEN_INT || 
        op1.data._TOKEN_TYPE == _TOKEN_PLUS ||
        op1.data._TOKEN_TYPE == _TOKEN_MINUS || 
        op1.data._TOKEN_TYPE == _TOKEN_MUL || 
        op1.data._TOKEN_TYPE == _TOKEN_DIV)
    {
        solveExpressionAndAssignValue(op1, solveExpression(op1));
    }

    if(op2.data._TOKEN_TYPE == _TOKEN_INT ||
        op2.data._TOKEN_TYPE == _TOKEN_PLUS ||
        op2.data._TOKEN_TYPE == _TOKEN_MINUS ||
        op2.data._TOKEN_TYPE == _TOKEN_MUL ||
        op2.data._TOKEN_TYPE == _TOKEN_DIV
        )
    {
        solveExpressionAndAssignValue(op2, solveExpression(op2));
    }

    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateElseByteCode(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateWhileByteCode(Token op, Tree op1, Tree op2){

    solveExpressionAndAssignValue(op1, solveExpression(op1));
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

    else if(root.data._TOKEN_TYPE == _TOKEN_IF || root.data._TOKEN_TYPE == _TOKEN_ELIF){
        generateIfByteCode(root.get_child(0).data, root.get_child(1), root.get_child(2));
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_ELSE){
        // Tree op1 (makeToken(_TOKEN_EMPTY,"","",0, 0));
        // Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
        generateElseByteCode(root.data, root.data, root.data);
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_WHILE){
        Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
        generateWhileByteCode(root.data, root.get_child(0), op2);
    }
}
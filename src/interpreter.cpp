#include "../include/interpreter.hpp"
#include "../include/core.hpp"
#include "../include/token.hpp"
#include "../include/vm.hpp"
#include "../include/map.hpp"
#include <unordered_map>
#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include <ctype.h>

std::unordered_map<TOKEN_T, MEOW_BYTE_CODE> token_byte_code_relation{
    {_TOKEN_EQU, _OP_SET},
    {_TOKEN_SHOW, _OP_OUT},
    {_TOKEN_TAKE, _OP_IN},
    {_TOKEN_EQUALSTO, _OP_CMP_EQU},
    {_TOKEN_LESSTHAN, _OP_CMP_LESS},
    {_TOKEN_LESSEQU, _OP_CMP_LESSEQU},
    {_TOKEN_GREATEREQU, _OP_CMP_GREAEQU},
    {_TOKEN_GREATERTHAN, _OP_CMP_GREATER},
    {_TOKEN_NOTEQUALS, _OP_CMP_NOTEQU},
    {_TOKEN_ENDIF, _OP_ENDIF},
    {_TOKEN_ENDELSE, _OP_ENDELSE},
    {_TOKEN_ELSE, _OP_ELSE},
    {_TOKEN_WHILE, _OP_LOOP}
};

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
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MOD){

        return std::fmod(solveExpression(root.get_child(0)), solveExpression(root.get_child(1)));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token var = get(root.data);
        return std::stold(var._TOKEN_VALUE);
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

bool isOperator(Token op)
{
    if(
        op._TOKEN_TYPE == _TOKEN_PLUS ||
        op._TOKEN_TYPE == _TOKEN_MINUS ||
        op._TOKEN_TYPE == _TOKEN_MUL ||
        op._TOKEN_TYPE == _TOKEN_DIV ||
        op._TOKEN_TYPE == _TOKEN_MOD
        )
    {
        return true;
    }

    return false;
}

void solveExpressionAndAssignValue(Tree &op, long double val){
    if( isOperator(op.data)
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

    if(op2.data._TOKEN_TYPE == _TOKEN_INT || isOperator(op2.data))
    {
        solveExpressionAndAssignValue(op2, solveExpression(op2));
    }

    else if(op2.data._TOKEN_TYPE == _TOKEN_TAKE){
        std::string input;
        std::cout << format_string(op2.get_child(0).data._TOKEN_VALUE);
        getline(std::cin, input);
        Token val;
        // check if the input is a int or string
        if(isdigit(input[0]))
        {
            val = makeToken(_TOKEN_INT, input, "", current_instruction.operand_1._TOKEN_LINE_NUMBER, current_instruction.operand_1._INDENTATION);
        }
        else
        {
            val = makeToken(_TOKEN_STRING, input, "", current_instruction.operand_1._TOKEN_LINE_NUMBER, current_instruction.operand_1._INDENTATION);
        }

        op2.data = val;
    }

    insert(op1.data, op2.data);
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateShowByteCode(Token op, Tree op1){

    if(op1.data._TOKEN_TYPE == _TOKEN_INT || 
        isOperator(op1.data))
    {
        solveExpressionAndAssignValue(op1, solveExpression(op1));
    }

    Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateIfByteCode(Token op, Tree op1, Tree op2){

    if(op1.data._TOKEN_TYPE == _TOKEN_INT || isOperator(op1.data))
    {
        solveExpressionAndAssignValue(op1, solveExpression(op1));
    }

    if(op2.data._TOKEN_TYPE == _TOKEN_INT || isOperator(op2.data))
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

void Interpreter::generateEndifnEndElse(Token op, Tree op1, Tree op2)
{
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::generateTakeByteCode(Token op, Tree op1, Tree op2)
{
    createAndSubmitByteCode(op, op1.data, op2.data);
}

void Interpreter::convertToByteCode(Tree root) {

    if(root.data._TOKEN_TYPE == _TOKEN_VAR){
        Tree op1 = root;                            // var
        Tree optr = op1.get_child(0);               // equals 
        if(optr.data._TOKEN_TYPE == _TOKEN_EQU){
            Tree op2 = optr.get_child(0);           // + - / * or string or take

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
        generateElseByteCode(root.data, root, root);
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_ENDIF ||
        root.data._TOKEN_TYPE == _TOKEN_ENDELSE)
        {
            generateEndifnEndElse(root.data, root, root);
        }

    else if(root.data._TOKEN_TYPE == _TOKEN_WHILE){
        Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
        generateWhileByteCode(root.data, root.get_child(0), op2);
    }
}
#include "../include/interpreter.hpp"
#include "../include/core.hpp"
#include "../include/token.hpp"
#include "../include/vm.hpp"
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
    {_TOKEN_WHILE, _OP_LOOP},
    {_TOKEN_ENDWHILE, _OP_ENDWHILE},
};



void createAndSubmitByteCode(Token oper, Tree oper1, Tree oper2){
    submitByteCode(
        makeByteCode(
            token_byte_code_relation[oper._TOKEN_TYPE],
            oper1,
            oper2
        )
    );
}

std::string cleanString(std::string str)
{
    std::string newStr = "";
    newStr += '"';
    for(int i = 0; i < str.size(); i++)
    {
        if(isalpha(str[i])) newStr+=str[i];
    }
    newStr += '"';

    return newStr;
}

std::string resolveString(Tree root)
{
    std::string joinedString = root.data._TOKEN_VALUE;

    if(root.childs.size() > 0) return joinedString += resolveString(root.get_child(0));

    return joinedString;
}

void Interpreter::generateAssignmentByteCode(Token op, Tree op1, Tree op2) {
    if(op2.data._TOKEN_TYPE == _TOKEN_STRING)
    {
        op2.data._TOKEN_VALUE = cleanString(resolveString(op2));
    }
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::generateShowByteCode(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::generateIfByteCode(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::generateElseByteCode(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::generateWhileByteCode(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::generateEndifnEndElse(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::generateTakeByteCode(Token op, Tree op1, Tree op2){
    createAndSubmitByteCode(op, op1, op2);
}

void Interpreter::convertToByteCode(Tree root) {

    if(root.data._TOKEN_TYPE == _TOKEN_VAR){
        Tree op1 = root;                            // var
        Tree optr = op1.get_child(0);               // equals 
        if(optr.data._TOKEN_TYPE == _TOKEN_EQU){
            Tree op2 = optr.get_child(0);           // + - / * or string or take

            if(op2.data._TOKEN_TYPE == _TOKEN_TAKE)
            {
                generateTakeByteCode(op2.data, op1, op2.get_child(0));
            }

            else generateAssignmentByteCode(optr.data, op1, op2);
        }
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_SHOW){
        Tree op2 (makeToken(_TOKEN_EMPTY,"","",0, 0));
        generateShowByteCode(root.data, root.get_child(0), op2);
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_IF || root.data._TOKEN_TYPE == _TOKEN_ELIF){
        Tree cmp_op = root.get_child(0);
        generateIfByteCode(cmp_op.data, cmp_op.get_child(1), cmp_op.get_child(0));
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_ELSE){
        generateElseByteCode(root.data, root, root);
    }

    else if(root.data._TOKEN_TYPE == _TOKEN_ENDIF ||
        root.data._TOKEN_TYPE == _TOKEN_ENDELSE   ||
        root.data._TOKEN_TYPE == _TOKEN_ENDWHILE)
        {
            generateEndifnEndElse(root.data, root, root);
        }

    else if(root.data._TOKEN_TYPE == _TOKEN_WHILE){
        createAndSubmitByteCode(root.data, root, root);
        Tree cmp_op = root.get_child(0);
        generateWhileByteCode(cmp_op.data, cmp_op.get_child(1), cmp_op.get_child(0));
    }
}
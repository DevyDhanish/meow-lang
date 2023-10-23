#include "../include/error.hpp"
#include <unordered_map>
#include "../include/token.hpp"
#include "../include/vm.hpp"
#include <iostream>
#include <vector>

std::unordered_map<Error_T, std::string> error_table = 
{
    {_E_SYNTAX_ERROR, "Syntax Error at %lu : %s"},
    {_E_CMP_ERROR, "Comparison Error at %lu : %s"},
    {_E_TYPE_ERROR, "Type Error at %lu : %s"},
    {_E_INDENTATION_ERROR, "Indentation Error at %lu : %s"},
    {_E_UNKNOW_TOKEN_ERROR, "Unknow Token at %lu : %s"},
};

int counter = 0;
std::vector<Token> TOKENS;

void displayError(Error_T error_type, std::string _line, size_t line_number) {
    printf(error_table[error_type].c_str(), line_number, _line.c_str());
    printf("\n");
    exit(0);
}

void checkOperator(Token next)
{
    switch (next._TOKEN_TYPE)
    {
    case _TOKEN_INT:
        break;

    default:
        Token prev = TOKENS[--counter];
        displayError(_E_SYNTAX_ERROR, prev._TOKEN_LINE, prev._TOKEN_LINE_NUMBER);
        break;
    }   
}

void checkInt(Token next)
{
    switch (next._TOKEN_TYPE)
    {
    case _TOKEN_SEMI_COL:
        break;
    case _TOKEN_PLUS:
        checkOperator(TOKENS[++counter]);
        break;
    case _TOKEN_MINUS:
        checkOperator(TOKENS[++counter]);
        break;
    case _TOKEN_MUL:
        checkOperator(TOKENS[++counter]);
        break;
    case _TOKEN_DIV:
        checkOperator(TOKENS[++counter]);
        break;
    case _TOKEN_MOD:
        checkOperator(TOKENS[++counter]);
        break;
    case _TOKEN_NEW_LINE:
        break;
    case _TOKEN_NOTEQUALS:
        break;
    case _TOKEN_EQUALSTO:
        break;
    case _TOKEN_LESSTHAN:
        break;
    case _TOKEN_LESSEQU:
        break;
    case _TOKEN_GREATEREQU:
        break;
    case _TOKEN_GREATERTHAN:
        break;
    case _TOKEN_COLON:
        break;
    default:
        Token prev = TOKENS[--counter];
        displayError(_E_SYNTAX_ERROR, prev._TOKEN_LINE, prev._TOKEN_LINE_NUMBER);
        break;
    }
}

void checkStr(Token next)
{
    switch (next._TOKEN_TYPE)
    {
    case _TOKEN_SEMI_COL:
        break;
    
    default:
        Token prev = TOKENS[--counter];
        displayError(_E_SYNTAX_ERROR, prev._TOKEN_LINE, prev._TOKEN_LINE_NUMBER);
        break;
    }
}

void checkShow(Token next)
{
    switch(next._TOKEN_TYPE)
    {
        case _TOKEN_STRING:
            checkStr(TOKENS[++counter]);
            break;

        case _TOKEN_PIKA:
            break;
        case _TOKEN_AYO:
            break;
        case _TOKEN_BEERUS:
            break;
        case _TOKEN_MEOWTH:
            break;
        case _TOKEN_NEW_LINE:
            break;

        case _TOKEN_INT:
            checkInt(TOKENS[++counter]);
            break;

        default:
            displayError(_E_SYNTAX_ERROR, next._TOKEN_LINE, next._TOKEN_LINE_NUMBER);
            break;
    }
}
void checkSyntax(std::vector<Token> tokens)
{
    TOKENS = tokens;
    while(counter < TOKENS.size())
    {
        Token curr = TOKENS[counter];

        if(curr._TOKEN_TYPE == _TOKEN_SHOW)
        {   
            ++counter;
            Token next = TOKENS[counter];
            checkShow(next);
        }

        counter++;
    }

    return;
}
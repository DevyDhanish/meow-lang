#include "../include/error.hpp"
#include <unordered_map>
#include "../include/token.hpp"
#include "../include/vm.hpp"

std::unordered_map<Error_T, std::string> error_table = 
{
    {_E_SYNTAX_ERROR, "Syntax Error at %lu : %s"},
    {_E_CMP_ERROR, "Comparison Error at %lu : %s"},
    {_E_TYPE_ERROR, "Type Error at %lu : %s"},
};
int counter = 0;
std::vector<Token> TOKENS;

void displayError(Error_T error_type, std::string _line, size_t line_number) {
    printf(error_table[error_type].c_str(), line_number, _line.c_str());
    printf("\n");
    exit(0);
}

void checkVar(Token next)
{
    if(next._TOKEN_TYPE == _TOKEN_SEMI_COL || next._TOKEN_TYPE == _TOKEN_COLON)
    {
        return;
    }
    else if(isOperator(next))
    {
        return;
    }
    else
    {
        displayError(_E_SYNTAX_ERROR, next._TOKEN_LINE, next._TOKEN_LINE_NUMBER);
    }
}
void checkStr(Token next)
{

    if(next._TOKEN_TYPE == _TOKEN_SEMI_COL || next._TOKEN_TYPE == _TOKEN_COLON)
    {
        return;
    }
    else if(next._TOKEN_TYPE == _TOKEN_VAR)
    {
        counter++;
        checkVar(TOKENS[counter]);
    }
    else if(next._TOKEN_TYPE == _TOKEN_INT)
    {
        counter++;
        //checkInt(TOKENS[counter]);
    }
    else
    {
        counter--;
        next = TOKENS[counter];
        displayError(_E_SYNTAX_ERROR, next._TOKEN_LINE, next._TOKEN_LINE_NUMBER);
    }
}

void checkShow(Token next)
{
    if(next._TOKEN_TYPE == _TOKEN_STRING)
    {
        counter++;
        checkStr(TOKENS[counter]);
    }
    else if(next._TOKEN_TYPE == _TOKEN_VAR)
    {
        counter++;
        checkVar(TOKENS[counter]);
    }
    else if(next._TOKEN_TYPE == _TOKEN_INT)
    {
        counter++;
        //checkInt(TOKENS[counter]);
    }
    else
    {
        displayError(_E_SYNTAX_ERROR, next._TOKEN_LINE, next._TOKEN_LINE_NUMBER);
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
            counter++;
            checkShow(TOKENS[counter]);
        }
        
        counter++;
    }

    return;
}
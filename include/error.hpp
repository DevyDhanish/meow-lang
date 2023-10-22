#ifndef ERROR_H
#define ERROR_H

#include "tree.hpp"
#include <unordered_map>

typedef enum ERROR_TYPE 
{
    _E_SYNTAX_ERROR,            // 0
    _E_TYPE_ERROR,              // 1
    _E_CMP_ERROR,               // 2
    _E_UNKNOW_TOKEN_ERROR,      // 3
} Error_T;

extern std::unordered_map<Error_T, std::string> error_table;


void displayError(Error_T error_type, std::string _line, size_t line_number);
void checkSyntax(std::vector<Token> tokens);
void checkInt(Token);
void checkEqu(Token);
void checkVar(Token);
void checkStr(Token);
void checkShow(Token);
void checkSyntax();

#endif
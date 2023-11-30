#include "../../include/token.hpp"
#include <string>
#include <vector>

std::vector<std::string> token_names_for_loging
{
    "_TOKEN_PLUS",     // 0
    "_TOKEN_MINUS",    // 1
    "_TOKEN_DIV",    // 2
    "_TOKEN_MUL",    // 3
    "_TOKEN_MOD",    // 4
    "_TOKEN_LESSTHAN",    // 5
    "_TOKEN_GREATERTHAN",    // 6
    "_TOKEN_LESSEQU",    // 7
    "_TOKEN_GREATEREQU",    // 8
    "_TOKEN_PLUSEQU",    // 9
    "_TOKEN_MINUSEQU",    // 10
    "_TOKEN_VAR",    // 11
    "_TOKEN_SHOW",    // 12
    "_TOKEN_RETURN",    // 13
    "_TOKEN_STRING",    // 14
    "_TOKEN_INT",    // 15
    "_TOKEN_NULL",    // 16
    "_TOKEN_SEMI_COL",    // 17
    "_TOKEN_WHILE",    // 18
    "_TOKEN_FOR",    // 19
    "_TOKEN_IF",    // 20
    "_TOKEN_ELSE",    // 21
    "_TOKEN_ELIF",    // 22
    "_TOKEN_START",    // 23
    "_TOKEN_EQU",    // 24
    "_TOKEN_CURLOPEN",    // 25
    "_TOKEN_CURLCLOSE",    // 26
    "_TOKEN_BRAOPEN",    // 27
    "_TOKEN_BRACLOSE",    // 28
    "_TOKEN_COLON",    // 29
    "_TOKEN_EMPTY",    // 30
    "_TOKEN_BEERUS",    // 31
    "_TOKEN_MEOWTH",    // 32
    "_TOKEN_PIKA",    // 33
    "_TOKEN_AYO",    // 34
    "_TOKEN_THEN",    // 35
    "_TOKEN_EQUALSTO",    // 36
    "_TOKEN_NOTEQUALS",    // 37
    "_TOKEN_MULEQUALS",    // 38
    "_TOKEN_DIVEQUALS",    // 39
    "_TOKEN_MODEQUALS",    // 40
    "_TOKEN_NOT",    // 41
    "_TOKEN_SQRBRAOPEN",    // 42
    "_TOKEN_SQRBRACLOSE",    // 43
    "_TOKEN_ENDIF",    // 44
    "_TOKEN_ENDELSE",    // 45
    "_TOKEN_TAKE",    // 46
    "_TOKEN_TRUE",    // 47
    "_TOKEN_FALSE",    // 48
    "_TOKEN_ENDWHILE",    // 49
    "_TOKEN_NEW_LINE",    // 50
    "_TOKEN_MASTRUBATE",    // 51  
};

Token makeToken(TOKEN_T _token_type, std::string _token_value, std::string _token_line, size_t _token_line_number, int _indentation){
    Token _new_token;

    _new_token._TOKEN_TYPE          = _token_type;
    _new_token._TOKEN_VALUE         = _token_value;
    _new_token._TOKEN_LINE          = _token_line;
    _new_token._TOKEN_LINE_NUMBER   = _token_line_number;
    _new_token._INDENTATION         = _indentation;
    
    return _new_token;
}
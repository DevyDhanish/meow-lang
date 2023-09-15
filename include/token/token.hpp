#pragma once

#include <string>

typedef enum _STRUCT_TOKEN_TYPE{

    _TOKEN_PLUS,            // 0
    _TOKEN_MINUS,           // 1
    _TOKEN_DIV,             // 2
    _TOKEN_MUL,             // 3
    _TOKEN_MOD,             // 4
    _TOKEN_LESSTHAN,        // 5
    _TOKEN_GREATERTHAN,     // 6
    _TOKEN_LESSEQU,         // 7
    _TOKEN_GREATEREQU,      // 8
    _TOKEN_PLUSEQU,         // 9
    _TOKEN_MINUSEQU,        // 10
    _TOKEN_VAR,             // 11
    _TOKEN_SHOW,            // 12
    _TOKEN_RETURN,          // 13
    _TOKEN_STRING,          // 14
    _TOKEN_INT,             // 15
    _TOKEN_NULL,            // 16
    _TOKEN_SEMI_COL,        // 17
    _TOKEN_WHILE,           // 18
    _TOKEN_FOR,             // 19
    _TOKEN_IF,              // 20
    _TOKEN_ELSE,            // 21
    _TOKEN_ELIF,            // 22
    _TOKEN_START,           // 23
    _TOKEN_EQU,             // 24
    _TOKEN_CURLOPEN,        // 25
    _TOKEN_CURLCLOSE,       // 26
    _TOKEN_BRAOPEN,         // 27
    _TOKEN_BRACLOSE,        // 28

}TOKEN_T;

typedef struct _STRUCT_TOKEN{
    TOKEN_T         _TOKEN_TYPE;
    std::string     _TOKEN_VALUE;
    std::string     _TOKEN_LINE;
    size_t          _TOKEN_LINE_NUMBER;
}Token;


Token _rt_struct_makeToken(TOKEN_T _token_type, std::string _token_value, std::string _token_line, size_t _token_line_number);
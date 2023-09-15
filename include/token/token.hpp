#pragma once

#include <string>

typedef enum _STRUCT_TOKEN_TYPE{

    _TOKEN_PLUS,
    _TOKEN_MINUS,
    _TOKEN_DIV,
    _TOKEN_MUL,
    _TOKEN_MOD,
    _TOKEN_VAR,
    _TOKEN_SHOW,
    _TOKEN_RETURN,
    _TOKEN_STRING,
    _TOKEN_INT,
    _TOKEN_NULL,
    _TOKEN_SEMI_COL,
    _TOKEN_START
}TOKEN_T;

typedef struct _STRUCT_TOKEN{
    TOKEN_T         _TOKEN_TYPE;
    std::string     _TOKEN_VALUE;
    std::string     _TOKEN_LINE;
    size_t          _TOKEN_LINE_NUMBER;
}Token;


Token _rt_struct_makeToken(TOKEN_T _token_type, std::string _token_value, std::string _token_line, size_t _token_line_number);
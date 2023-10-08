#include "../include/token.hpp"
#include <string>

Token makeToken(TOKEN_T _token_type, std::string _token_value, std::string _token_line, size_t _token_line_number){
    Token _new_token;

    _new_token._TOKEN_TYPE          = _token_type;
    _new_token._TOKEN_VALUE         = _token_value;
    _new_token._TOKEN_LINE          = _token_line;
    _new_token._TOKEN_LINE_NUMBER   = _token_line_number;

    return _new_token;
}
#include "../include/core.hpp"
#include "../include/token.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <set>

std::unordered_map<std::string, TOKEN_T> knowTokens = {
        {"show", _TOKEN_SHOW},
        {"beerus", _TOKEN_BEERUS},
        {"meowth", _TOKEN_MEOWTH},
        {"pika", _TOKEN_PIKA},
        {"ayo", _TOKEN_AYO},
        {"mastrubate", _TOKEN_MASTRUBATE},
        {"return", _TOKEN_RETURN},
        {"null", _TOKEN_NULL},
        {"=", _TOKEN_EQU},
        {"==", _TOKEN_EQUALSTO},
        {"!=", _TOKEN_NOTEQUALS},
        {"!", _TOKEN_NOT},
        {"<", _TOKEN_LESSTHAN},
        {"<=", _TOKEN_LESSEQU},
        {">=", _TOKEN_GREATEREQU},
        {">", _TOKEN_GREATERTHAN},
        {"+", _TOKEN_PLUS},
        {"+=", _TOKEN_PLUSEQU},
        {"-", _TOKEN_MINUS},
        {"-=", _TOKEN_MINUSEQU},
        {"*", _TOKEN_MUL},
        {"*=", _TOKEN_MULEQUALS},
        {"/", _TOKEN_DIV},
        {"/=", _TOKEN_DIVEQUALS},
        {"%", _TOKEN_MOD},
        {"%=", _TOKEN_MODEQUALS},
        {"(", _TOKEN_BRAOPEN},
        {")", _TOKEN_BRACLOSE},
        {"{", _TOKEN_CURLOPEN},
        {"}", _TOKEN_CURLCLOSE},
        {"[", _TOKEN_SQRBRAOPEN},
        {"]", _TOKEN_SQRBRACLOSE},
        {"while", _TOKEN_WHILE},
        {"for", _TOKEN_FOR},
        {"if", _TOKEN_IF},
        {"then", _TOKEN_THEN},
        {"elif", _TOKEN_ELIF},
        {"else", _TOKEN_ELSE},
        {"fi", _TOKEN_ENDIF},
        {"el", _TOKEN_ENDELSE},
        {":", _TOKEN_COLON},
        {";", _TOKEN_SEMI_COL},
        {"take", _TOKEN_TAKE},
        {"end", _TOKEN_ENDWHILE},
        {"nl", _TOKEN_NEW_LINE},
};

std::unordered_map<char, std::string> operator_pair = {
    {'=', "=="},
    {'!', "!="},
    {'<', "<="},
    {'>', ">="},
    {'+', "+="},
    {'-', "-="},
    {'*', "*="},
    {'/', "/="},
    {'%', "%="},
    {':', ":"},
    {';', ";"},
};

std::set<char> brackets = {
    '(',
    ')',
    '{',
    '}',
    '[',
    ']',
};

bool isEmpty(std::string curr_line){
    for(char i : curr_line){
        if(i != ' ') return 0;
   }
    return 1;
}

// @brief convert file line to meow_line
// @returns vector of meow_line
std::vector<meow_line> file_to_vect(std::string _prog_filename){

    std::ifstream _prog_file (_prog_filename);          
    std::vector<meow_line> _prog_lines_vect;
    size_t line_number = 1;

    std::string _prog_line;
    while(_prog_file){
        getline(_prog_file, _prog_line);

        if(!isEmpty(_prog_line)){                            // skip the empty lines
            meow_line _line;
            _line.line = _prog_line;
            _line.line_number = line_number;
            _prog_lines_vect.push_back(_line);
        }

        _prog_line = "";
        line_number += 1;
    }

    return _prog_lines_vect;
}

std::string format_string(std::string _str){
    std::string f_string =  "";

    for(char i : _str){
        if(i != '"') f_string += i;
    }

    return f_string;
}
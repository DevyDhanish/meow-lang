#include "../include/lexer.hpp"
#include "../include/token.hpp"
#include "../include/core.hpp"

#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <iostream>


int LINE_IDENTATION = 0;

// check if current words is a token or not
int _helper_isToken(std::string val){
    std::vector<std::string> known_tokens = {
        "show",
        "return",
        "null",
        "if",
        "else",
        "while",
        "for",
        "beerus",
        "meowth",
        "then",
    };

    for(size_t i = 0 ; i < known_tokens.size(); i++){
        if(val == known_tokens[i]) return 1;
    }

    return 0;
}

// check if current word is a operator
int _helper_isOperator(char ch){
    std::string ops = "{}[]()";

    for(int i = 0; i < (int)ops.size(); i++){
        if(ch == ops[i]) return 1;
    }

    return 0;
}

int _helper_isString(std::string word){
    if(word[0] == '"' && word[word.size() - 1] == '"') return 1;

    else return 0;
}

// used to disassemble line into words for example line ` x = 5 + 5;` will be disassembled into `x,=,5,+,5,;`
// This method will be called for each line
std::vector<std::string> _helper_disassemble_line(meow_line line){

    std::vector<std::string> output;                                // each disassembled word will be pushed into this vector
    std::string curr_line = line.line;
    size_t curr_pos = 0;

    while(curr_pos < curr_line.size()){                             // loop until it reaches the end of the line
        char lookAhead = curr_line[curr_pos];

        for(char i : curr_line){
            if(i != ' ') break;
            if(i == ' ') LINE_IDENTATION += 1;
        }

        if(lookAhead == ' '){                                       // ignore space
            curr_pos += 1;
        }
        else if (lookAhead == '='){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("==");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '>'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back(">=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '<'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("<=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '+'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("+=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '-'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("-=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '*'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("*=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '/'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("/=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '%'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("%=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if (lookAhead == '!'){
            curr_pos += 1;

            if(curr_line[curr_pos] == '=')
                output.push_back("!=");
            else
                output.push_back(std::string(1,lookAhead));

            curr_pos += 1;
        }
        else if(_helper_isOperator(lookAhead)){
            output.push_back(std::string(1, lookAhead));
            curr_pos += 1;
        }
        else if ( lookAhead == ':'){
            output.push_back(std::string(1, lookAhead));
            curr_pos += 1;
        }
        else if (lookAhead == '"'){                                 // if a string is detected sorround it with `"` for example `this is a string` will become "this is a string"
            std::string word;
            word += '"';
            curr_pos += 1;
            while(curr_line[curr_pos] != '"'){
                word += curr_line[curr_pos];
                curr_pos += 1;

                if(curr_pos > curr_line.size()){
                    std::cout << "Syntax error: at line " << line.line_number << " missing `\"` at the end of the string" << "\n";          // change the way errors are shown
                    break;
                }
            }
            word += '"';
            if(word != "")
                output.push_back(word);
            else{
                //std::cout << "Empty string\n";
                break;
            };
            curr_pos += 1;
        }

        else if (isdigit(lookAhead)){
            std::string word;
            while(curr_pos < curr_line.size() && isalnum(curr_line[curr_pos])){
                word += curr_line[curr_pos];
                curr_pos += 1;
            }

            if(word != "")
                output.push_back(word);
                
            else output.push_back(std::string(1,lookAhead));
        }

        else if (isalpha(lookAhead)){
            std::string word;
            while(curr_pos < curr_line.size() && isalpha(curr_line[curr_pos])){
                word += curr_line[curr_pos];
                curr_pos += 1;
            }

            if(word != "")
                output.push_back(word);
            else output.push_back(std::string(1,lookAhead));
        }
        else if (lookAhead == ';'){ 
            output.push_back(std::string(1, lookAhead));
            curr_pos += 1;
        }

        else{
            std::cout << "Unknown token: encountered " << "`" << lookAhead << "`" << " at line " << line.line_number << "\n";
            break;
        }

    }

    return output;
}

// @brief the given vector of "meow_line" to a vector of respective tokens
std::vector<Token> Lexer::tokenize(meow_line _prog_lines){

    std::vector<Token> _prog_token_list;
    LINE_IDENTATION = 0;
    std::vector<std::string> words = _helper_disassemble_line(_prog_lines);

    for(std::string curr_word : words){
        
        if(curr_word == "show"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_SHOW, 
                curr_word, 
                _prog_lines.line, 
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "beerus"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_BEERUS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "meowth"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MEOWTH,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "pika"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_PIKA,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "ayo"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_AYO,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "return"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_RETURN, 
                curr_word, 
                _prog_lines.line, 
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "null"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_NULL, 
                curr_word, 
                _prog_lines.line, 
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_EQU,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "=="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_EQUALSTO,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "!="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_NOTEQUALS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "!"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_NOT,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "<"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_LESSTHAN,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "<="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_LESSEQU,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == ">="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_GREATEREQU,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == ">"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_GREATERTHAN,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "+"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_PLUS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "+="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_PLUSEQU,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "-"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MINUS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "-="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MINUSEQU,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "*"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MUL,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "*="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MULEQUALS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "/"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_DIV,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "/="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_DIVEQUALS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "%"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MOD,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "%="){
            _prog_token_list.push_back(makeToken(
                _TOKEN_MODEQUALS,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "("){
            _prog_token_list.push_back(makeToken(
                _TOKEN_BRAOPEN,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == ")"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_BRACLOSE,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "{"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_CURLOPEN,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "}"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_CURLCLOSE,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(_helper_isString(curr_word)){
            _prog_token_list.push_back(makeToken(
                _TOKEN_STRING,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }

        else if(isdigit(curr_word[0])){
            _prog_token_list.push_back(makeToken(
                _TOKEN_INT,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "while"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_WHILE,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "if"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_IF,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "then"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_THEN,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "elif"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_ELIF,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == "else"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_ELSE,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == ":"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_COLON,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(curr_word == ";"){
            _prog_token_list.push_back(makeToken(
                _TOKEN_SEMI_COL,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else if(!_helper_isToken(curr_word)){
            _prog_token_list.push_back(makeToken(
                _TOKEN_VAR,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else{
            std::cout << "ERROR in lexing\n";
            exit(0);
        }
    }

    return _prog_token_list;
}    
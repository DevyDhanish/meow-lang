#include "../../include/lexer/lexer.hpp"
#include "../../include/token/token.hpp"
#include "../../include/core/core.hpp"

#include <string>
#include <vector>
#include <map>

#include <iostream>

int _helper_isNum(std::string val){
    std::vector<char> nums = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    for(size_t i = 0; i < nums.size(); i++){
        if(val[0] == nums[i]) return 1;
    }

    return 0;
}

int _helper_isVar(std::string val){
    std::vector<std::string> knows_tokens = {
        "show",
        "return",
        "null"
    };

    for(size_t i = 0 ; i < knows_tokens.size(); i++){
        if(val == knows_tokens[i]) return 1;
    }

    return 0;
}

int _helper_isOperator(char ch){
    std::string ops = "/*+-=<>{}[]()";

    for(int i = 0; i < (int)ops.size(); i++){
        if(ch == ops[i]) return 1;
    }

    return 0;
}

int _helper_isString(std::string word){
    if(word[0] == '"' && word[word.size() - 1] == '"') return 1;
    else return 0;
}

std::vector<std::string> _helper_disassemble_line(meow_line line){

    std::vector<std::string> output;
    std::string curr_line = line.line;
    size_t curr_pos = 0;

    while(curr_pos < curr_line.size()){
        char lookAhead = curr_line[curr_pos];

        if(lookAhead == ' '){
            curr_pos += 1;
        }
        else if (_helper_isOperator(lookAhead)){
            output.push_back(std::string(1,lookAhead));
            curr_pos += 1;
        }
        else if (lookAhead == '"'){
            std::string word;
            word += '"';
            curr_pos += 1;
            while(curr_line[curr_pos] != '"'){
                word += curr_line[curr_pos];
                curr_pos += 1;

                if(curr_pos > curr_line.size()){
                    std::cout << "Syntax error: at line " << line.line_number << " missing `\"` at the end of the string" << "\n";
                    break;
                }
            }
            word += '"';
            if(word != "")
                output.push_back(word);
            else{
                std::cout << "Empty string\n";
                break;
            };
            curr_pos += 1;
        }
        else if (isalnum(lookAhead)){
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

void Lexer::_rt_None_tokenize(std::vector<meow_line> _prog_lines_vect){
    size_t counter = 0;

    while(_prog_lines_vect[counter].line != END_NODE){

        std::vector<std::string> words = _helper_disassemble_line(_prog_lines_vect[counter]);

        for(std::string curr_word : words){
            
            if(curr_word == "show"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_SHOW, curr_word, 
                    _prog_lines_vect[counter].line, 
                    _prog_lines_vect[counter].line_number
                    ));
            }
            else if(curr_word == "+"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_PLUS,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(curr_word == "-"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_MINUS,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(curr_word == "*"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_MUL,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(curr_word == "/"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_DIV,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(curr_word == "%"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_MOD,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(_helper_isString(curr_word)){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_STRING,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(_helper_isNum(curr_word)){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_INT,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else if(curr_word == ";"){
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_SEMI_COL,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
            else{
                this->_prog_token_list.push_back(_rt_struct_makeToken(
                    _TOKEN_VAR,
                    curr_word,
                    _prog_lines_vect[counter].line,
                    _prog_lines_vect[counter].line_number
                ));
            }
        }

        counter++;
    }
}

std::vector<Token> Lexer::_rt_token_gettokenizedlist(){
    return this->_prog_token_list;
}
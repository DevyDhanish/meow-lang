#include "../../include/lexer/lexer.hpp"
#include "../../include/token/token.hpp"

#include <string>
#include <vector>

#include <iostream>

void _helper_increment(size_t *counter){
    *counter += 1;
}

std::vector<std::string> _helper_disassemble_line(std::string line){
    std::vector<std::string> words;

    size_t line_lenght = line.size();
    size_t _counter = 0;

    std::string word;

    while(_counter <= line_lenght){
        if(line[_counter] == ' ' || line[_counter] == ';'){
            words.push_back(word);
            word = "";
        }
        else{
            word += line[_counter];
        }

        _helper_increment(&_counter);
    }

    words.push_back(";");
    return words;
}

void Lexer::_rt_None_tokenize(std::vector<std::string> _prog_lines_vect){
    size_t lenght = _prog_lines_vect.size();
    size_t l_counter = 0;
    size_t line_number = 1;

    while(l_counter < lenght){
        std::vector<std::string> words_in_line = _helper_disassemble_line(_prog_lines_vect[l_counter]);

        for(std::string word : words_in_line){
            
            if(word == "show"){
                this->_prog_token_list.push_back(
                    _rt_struct_makeToken(
                        _TOKEN_SHOW,
                        word,
                        _prog_lines_vect[l_counter],
                        line_number
                    )
                );
            }

            else if(word == "return"){
                this->_prog_token_list.push_back(
                    _rt_struct_makeToken(
                        _TOKEN_RETURN,
                        word,
                        _prog_lines_vect[l_counter],
                        line_number
                    )
                );
            }

            else if(word == ";"){
                this->_prog_token_list.push_back(
                    _rt_struct_makeToken(
                        _TOKEN_SEMI_COL,
                        word,
                        _prog_lines_vect[l_counter],
                        line_number
                    )
                );
            }

            else if(word == "0"){
                this->_prog_token_list.push_back(
                    _rt_struct_makeToken(
                        _TOKEN_INT,
                        word,
                        _prog_lines_vect[l_counter],
                        line_number
                    )
                );
            }
        }

        _helper_increment(&l_counter);
        _helper_increment(&line_number);
    }
}

std::vector<Token> Lexer::_rt_token_gettokenizedlist(){
    return this->_prog_token_list;
}
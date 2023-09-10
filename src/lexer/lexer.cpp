#include "../../include/lexer/lexer.hpp"
#include "../../include/token/token.hpp"
#include "../../include/core/core.hpp"

#include <string>
#include <vector>

#include <iostream>

int _helper_isOperator(char ch){
    std::string ops = "/*+-=";

    for(int i = 0; i < (int)ops.size(); i++){
        if(ch == ops[i]) return 1;
    }

    return 0;
}

void _helper_increment(size_t *counter){
    *counter += 1;
}

std::vector<std::string> _helper_disassemble_line(std::string line){

    std::vector<std::string> words;

    size_t curr_counter = 0;

    std::string word;

    char curr_ch;
    while(curr_ch != ';'){

        curr_ch = line[curr_counter];

        if(curr_ch == ' '){
            words.push_back(word);
            word = "";
        }

        else if(_helper_isOperator(curr_ch)){
            words.push_back(word);
            word = "";
        }
        
        word += curr_ch;

        _helper_increment(&curr_counter);
    }

    words.push_back(";");
    return words;
}

void Lexer::_rt_None_tokenize(std::vector<meow_line> _prog_lines_vect){
    size_t lenght = _prog_lines_vect.size();
    size_t l_counter = 0;

    while(l_counter < lenght){
        std::vector<std::string> words_in_line = _helper_disassemble_line(_prog_lines_vect[l_counter]._line);

        for(std::string word : words_in_line){

            std::cout << word << "\n";
            
            // if(word == "show"){
            //     this->_prog_token_list.push_back(
            //         _rt_struct_makeToken(
            //             _TOKEN_SHOW,
            //             word,
            //             _prog_lines_vect[l_counter]._line,
            //             _prog_lines_vect[l_counter].line_number
            //         )
            //     );
            // }

            // else if(word == "return"){
            //     this->_prog_token_list.push_back(
            //         _rt_struct_makeToken(
            //             _TOKEN_RETURN,
            //             word,
            //             _prog_lines_vect[l_counter]._line,
            //             _prog_lines_vect[l_counter].line_number
            //         )
            //     );
            // }

            // else if(word == ";"){
            //     this->_prog_token_list.push_back(
            //         _rt_struct_makeToken(
            //             _TOKEN_SEMI_COL,
            //             word,
            //             _prog_lines_vect[l_counter]._line,
            //             _prog_lines_vect[l_counter].line_number
            //         )
            //     );
            // }

            // else if(word == "0"){
            //     this->_prog_token_list.push_back(
            //         _rt_struct_makeToken(
            //             _TOKEN_INT,
            //             word,
            //             _prog_lines_vect[l_counter]._line,
            //             _prog_lines_vect[l_counter].line_number
            //         )
            //     );
            // }
        }

        _helper_increment(&l_counter);
    }
}

std::vector<Token> Lexer::_rt_token_gettokenizedlist(){
    return this->_prog_token_list;
}
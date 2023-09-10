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

std::vector<std::string> _helper_disassemble_line(meow_line line){

    std::vector<std::string> output;
    std::string curr_line = line.line;
    size_t curr_line_lenght = curr_line.size();

    return output;
}

void Lexer::_rt_None_tokenize(std::vector<meow_line> _prog_lines_vect){
    size_t counter = 0;

    while(_prog_lines_vect[counter].line != END_NODE){

        std::vector<std::string> words = _helper_disassemble_line(_prog_lines_vect[counter]);

        for(std::string i : words){
            std::cout << i << "\n";
        }

        counter++;

        break;
    }
}

std::vector<Token> Lexer::_rt_token_gettokenizedlist(){
    return this->_prog_token_list;
}
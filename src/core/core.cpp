#include "../../include/core/core.hpp"
#include "../../include/token/token.hpp"
#include <vector>
#include <fstream>
#include <iostream>

std::vector<meow_line> file_to_vect(std::string _prog_filename){

    std::ifstream _prog_file (_prog_filename);
    std::vector<meow_line> _prog_lines_vect;
    size_t line_number = 1;

    std::string _prog_line;
    while(_prog_file){
        getline(_prog_file, _prog_line);

        if(!_prog_line.empty()){
            meow_line _line;
            _line.line = _prog_line;
            _line.line_number = line_number;
            _prog_lines_vect.push_back(_line);
        }

        _prog_line = "";
        line_number += 1;
    }

    meow_line END;
    END.line = END_NODE;
    END.line_number = line_number+1;
    _prog_lines_vect.push_back(END);
    return _prog_lines_vect;
}

// void VariableMap::add_var(Token key, Token val){
//     this->var_map[key] = val;
// }

// Token VariableMap::get_var(Token key){
//     return this->var_map[key];
// }

// void VariableMap::update_var(Token key, Token val){
//     this->var_map[key] = val;
// }
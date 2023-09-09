#include "../../include/core/core.hpp"
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::string> Core::file_to_vect(std::string _prog_filename){

    std::ifstream _prog_file (_prog_filename);
    std::vector<std::string> _prog_lines_vect;

    std::string _prog_line;
    while(_prog_file){
        getline(_prog_file, _prog_line);

        if(!_prog_line.empty()){
            _prog_lines_vect.push_back(_prog_line);
        }

        _prog_line = "";
    }

    return _prog_lines_vect;
}
#include "../include/core.hpp"
#include "../include/token.hpp"
#include <vector>
#include <fstream>
#include <iostream>

// @brief convert file line to meow_line
// @returns vector of meow_line
std::vector<meow_line> file_to_vect(std::string _prog_filename){

    std::ifstream _prog_file (_prog_filename);          
    std::vector<meow_line> _prog_lines_vect;
    size_t line_number = 1;

    std::string _prog_line;
    while(_prog_file){
        getline(_prog_file, _prog_line);

        if(!_prog_line.empty()){                            // skip the empty lines
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

    _prog_lines_vect.push_back(END);                        // set a end node __END__ at the end of the vector,
                                                            // don't really need it but look cool i guess.
    return _prog_lines_vect;
}
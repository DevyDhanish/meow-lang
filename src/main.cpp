#include <iostream>
#include <vector>

#include "../include/core/core.hpp"
#include "../include/lexer/lexer.hpp"
#include "../include/token/token.hpp"

using std::vector;
using std::cout;
using std::string;


int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "NO, input file" << "\n";
        return 0;
    }

    Lexer lex;

    vector<meow_line> _prog_lines = file_to_vect(argv[1]);
    lex._rt_None_tokenize(_prog_lines);
    // for(meow_line i : _prog_lines){
    //     cout << i.line;
    // }

    return 0;
}
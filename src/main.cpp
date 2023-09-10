#include <iostream>
#include <fstream>
#include <vector>

#include "../include/core/core.hpp"
#include "../include/lexer/lexer.hpp"
#include "../include/token/token.hpp"

using std::vector;
using std::cout;
using std::ifstream;
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
    vector<Token>  _prog_token_list = lex._rt_token_gettokenizedlist();


    // for(Token t : _prog_token_list){
    //     cout << t._TOKEN_TYPE << ", " << t._TOKEN_LINE << ", " << t._TOKEN_VALUE << ", " << t._TOKEN_LINE_NUMBER << "\n";
    // }

    return 0;
}
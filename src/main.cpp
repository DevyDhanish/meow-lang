#include <iostream>
#include <vector>

#include "../include/core/core.hpp"
#include "../include/lexer/lexer.hpp"
#include "../include/token/token.hpp"
#include "../include/DS/tree.hpp"
#include "../include/parser/parser.hpp"

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
    std::vector<_STRUCT_TOKEN> tokenized_list = lex._rt_token_gettokenizedlist();
    Tree AST = _rt_Tree_parse(tokenized_list);

    AST._rt_None_print_tree();

    return 0;
}
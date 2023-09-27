#include "../../include/parser/parser.hpp"
#include "../../include/DS/tree.hpp"
#include "../../include/token/token.hpp"
#include "../../include/core/core.hpp"

#include <vector>
#include <iostream>

// x = 1 + 2;
// show x;
// AST of this code 
//                  program
//                  /     \ 
//            assignment  display
//             /     \       |
//            X      +       X
//                 /   \
//                1     2
// 

Token _helper_create_start_node(){
    Token start;
    start._TOKEN_TYPE = _TOKEN_START;
    start._TOKEN_VALUE = START_NODE;
    start._TOKEN_LINE = "";
    start._TOKEN_LINE_NUMBER = 0;

    return start;
}


Tree _rt_Tree_parse(std::vector<Token> prog_tokens){
    Tree root(_helper_create_start_node());

    for(auto i : prog_tokens){
        std::cout << i._TOKEN_VALUE << ",";
    }

    return root;
}
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

Tree parse_plus(size_t curr_pos, std::vector<Token> prog_tokes){
    
    Tree plus(prog_tokes[curr_pos]);

    plus._rt_None_add_child(Tree(prog_tokes[curr_pos - 1]));
    plus._rt_None_add_child(Tree(prog_tokes[curr_pos + 1]));

    return plus;
}

Tree parse_string(size_t curr_pos, std::vector<Token> prog_tokes){
    Tree st_lit(prog_tokes[curr_pos]);

    return st_lit;
}

Tree parse_var(size_t curr_pos, std::vector<Token> prog_tokes){

    Tree var(prog_tokes[curr_pos]);
    curr_pos++;

    while (prog_tokes[curr_pos]._TOKEN_TYPE != _TOKEN_SEMI_COL)
    {
        if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_VAR){
            var._rt_None_add_child(parse_var(curr_pos, prog_tokes));
        }

        else if (prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_STRING){
            var._rt_None_add_child(parse_string(curr_pos, prog_tokes));
        }

        else if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_PLUS){
            var._rt_None_add_child(parse_plus(curr_pos, prog_tokes));
        }

        curr_pos++;
    } 

    return var;
}

Tree parse_show(size_t curr_pos, std::vector<Token> prog_tokes){

    Tree show(prog_tokes[curr_pos]);
    curr_pos++;

    if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_VAR){
        show._rt_None_add_child(parse_var(curr_pos, prog_tokes));
        return show;
    }

    else if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_STRING){
        show._rt_None_add_child(parse_string(curr_pos, prog_tokes));
        return show;
    }

    return show;
}


Tree _rt_Tree_parse(std::vector<Token> prog_tokens){

    Tree root(_helper_create_start_node());

    for(size_t i = 0; i < prog_tokens.size(); i++){
        if(prog_tokens[i]._TOKEN_TYPE == _TOKEN_SHOW){
            root._rt_None_add_child(parse_show(i, prog_tokens));
        }

        else if(prog_tokens[i]._TOKEN_TYPE == _TOKEN_VAR){
            root._rt_None_add_child(parse_var(i, prog_tokens));
        }
    }

    return root;
}
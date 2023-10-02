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

Token _helper_create_empty_node(){
    Token empty;
    empty._TOKEN_TYPE = _TOKEN_NULL;
    empty._TOKEN_VALUE = "im empty bruh";
    empty._TOKEN_LINE = "adjfa";
    empty._TOKEN_LINE_NUMBER = 0;
}

void Parser::Eat(){
    if(this->prog_token_counter + 1 < this->meow_prog_tokens.size()){
        this->current_token = this->meow_prog_tokens[prog_token_counter];
    }
    else{
        this->current_token = _helper_create_empty_node();
    }
}

void Parser::setProg_Tokens(std::vector<Token> prog_tokes){
    this->meow_prog_tokens = prog_tokes;
}

Tree Parser::Parse(){
    Tree start_node(_helper_create_start_node());

    return start_node;
}

// Tree parse_plus(size_t curr_pos, std::vector<Token> prog_tokes){
    
//     Tree plus(prog_tokes[curr_pos]);

//     plus._rt_None_add_child(Tree(prog_tokes[curr_pos - 1]));
//     plus._rt_None_add_child(Tree(prog_tokes[curr_pos + 1]));

//     return plus;
// }

// Tree parse_string(size_t curr_pos, std::vector<Token> prog_tokes){
//     Tree st_lit(prog_tokes[curr_pos]);

//     return st_lit;
// }

// Tree parse_int(size_t curr_pos, std::vector<Token> prog_tokes){

//     if(prog_tokes[curr_pos + 1]._TOKEN_TYPE == _TOKEN_PLUS){
//         Tree int_node(parse_plus(curr_pos + 1, prog_tokes));
//         return int_node;
//     }
//     else{
//         Tree int_node(prog_tokes[curr_pos]);
//         return int_node;
//     }

// }

// Tree parse_equ(size_t curr_pos, std::vector<Token> prog_tokes){
    
//     Tree equ_node (prog_tokes[curr_pos]);
//     curr_pos++;

//     if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_PLUS){
//         equ_node._rt_None_add_child(parse_plus(curr_pos, prog_tokes));
//     }
//     else if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_INT){
//         equ_node._rt_None_add_child(parse_int(curr_pos, prog_tokes));
//     }

//     return equ_node;
// }

// Tree parse_var(size_t curr_pos, std::vector<Token> prog_tokes){

//     Tree var(prog_tokes[curr_pos]);
//     curr_pos++;

//     if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_EQU){
//         var._rt_None_add_child(parse_equ(curr_pos, prog_tokes));
//     }
//     else if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_VAR){
//         var._rt_None_add_child(parse_var(curr_pos, prog_tokes));
//     }
//     else if (prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_STRING){
//         var._rt_None_add_child(parse_string(curr_pos, prog_tokes));
//     }
//     else if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_PLUS){
//         var._rt_None_add_child(parse_plus(curr_pos, prog_tokes));
//     }

//     return var;
// }

// Tree parse_show(size_t curr_pos, std::vector<Token> prog_tokes){

//     Tree show(prog_tokes[curr_pos]);
//     curr_pos++;

//     if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_VAR){
//         show._rt_None_add_child(parse_var(curr_pos, prog_tokes));
//         return show;
//     }

//     else if(prog_tokes[curr_pos]._TOKEN_TYPE == _TOKEN_STRING){
//         show._rt_None_add_child(parse_string(curr_pos, prog_tokes));
//         return show;
//     }

//     return show;
// }


// Tree _rt_Tree_parse(std::vector<Token> prog_tokens){

//     Tree root(_helper_create_start_node());

//     for(size_t i = 0; i < prog_tokens.size(); i++){

//         if(prog_tokens[i]._TOKEN_TYPE == _TOKEN_SHOW){
//             root._rt_None_add_child(parse_show(i, prog_tokens));
//         }

//         else if(prog_tokens[i]._TOKEN_TYPE == _TOKEN_VAR){
//             root._rt_None_add_child(parse_var(i, prog_tokens));
//         }
//     }

//     return root;
// }
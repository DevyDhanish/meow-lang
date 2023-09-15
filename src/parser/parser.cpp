#include "../../include/parser/parser.hpp"
#include "../../include/DS/tree.hpp"
#include "../../include/token/token.hpp"
#include "../../include/core/core.hpp"

#include <vector>
#include <iostream>

Token _helper_create_start_node(){
    Token start;
    start._TOKEN_TYPE = _TOKEN_START;
    start._TOKEN_VALUE = START_NODE;
    start._TOKEN_LINE = "";
    start._TOKEN_LINE_NUMBER = 0;

    return start;
}

Tree parser_var(Token var){
    Tree node(var);
    return node;
}

void parse_assignment(std::vector<Token> toks){
    Tree output;

    size_t counter = 0;

    while(counter < toks.size()){
        Token curr_token = toks[counter];
        Token lookAhead = toks[counter + 1];

        if(lookAhead._TOKEN_TYPE == _TOKEN_PLUS){
            // create add node
        }
        else if (lookAhead._TOKEN_TYPE == _TOKEN_MINUS){
            // create minus node
        }
        else if (lookAhead._TOKEN_TYPE == _TOKEN_DIV){
            // create div node
        }
        else if (lookAhead._TOKEN_TYPE == _TOKEN_MUL){
            // create mul node
        }
        else if (lookAhead._TOKEN_TYPE == _TOKEN_MOD){
            // create mod node
        }
        else {
            std::cout << "Unknow operator " << "`" << curr_token._TOKEN_VALUE << "`" << " at line " << curr_token._TOKEN_LINE_NUMBER << "\n";
        }

        counter += 1;
    }
}

Tree _rt_Tree_parse(std::vector<Token> prog_tokens){
    Tree root(_helper_create_start_node());

    size_t counter = 0;

    while(counter < prog_tokens.size()){
        Token curr_token = prog_tokens[counter];
        Token lookAhead = prog_tokens[counter + 1];

        if(curr_token._TOKEN_TYPE == _TOKEN_VAR && lookAhead._TOKEN_TYPE == _TOKEN_SEMI_COL){
            root._rt_None_add_child(parser_var(curr_token));
            counter += 1;
        }

        else if(curr_token._TOKEN_TYPE == _TOKEN_VAR && lookAhead._TOKEN_TYPE == _TOKEN_EQU){
            counter += 2;
            std::vector<Token> rem_toks;

            while(prog_tokens[counter]._TOKEN_TYPE != _TOKEN_SEMI_COL && counter < prog_tokens.size()){
                rem_toks.push_back(prog_tokens[counter]);
                counter += 1;
            }
            rem_toks.push_back(prog_tokens[counter]);
            parse_assignment(rem_toks);
        }

        counter += 1;
    }

    return root;
}
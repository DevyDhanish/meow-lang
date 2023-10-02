#include <iostream>
#include <vector>
#include <unordered_map>
#include <string.h>

#include "../include/core/core.hpp"
#include "../include/lexer/lexer.hpp"
#include "../include/token/token.hpp"
#include "../include/DS/tree.hpp"
#include "../include/parser/parser.hpp"

using std::vector;
using std::cout;
using std::string;

vector<int> var_val;

std::unordered_map<string, int> var_map;

void execute(Tree root){

    if(root.data._TOKEN_TYPE == _TOKEN_SHOW){
        if(root.childs[0].data._TOKEN_TYPE == _TOKEN_STRING){
            std::cout << root.childs[0].data._TOKEN_VALUE << "\n";
        }
        else if(root.childs[0].data._TOKEN_TYPE == _TOKEN_VAR){
            std::cout << var_map[root.childs[0].data._TOKEN_VALUE] << "\n";
        }
    }

    else if (root.data._TOKEN_TYPE == _TOKEN_PLUS){
        //std::cout << root.childs[1].data._TOKEN_VALUE;
        var_map[root.parent->data._TOKEN_VALUE] = (stoi(root.childs[0].data._TOKEN_VALUE) + stoi(root.childs[1].data._TOKEN_VALUE));
    }

    else if (root.data._TOKEN_TYPE == _TOKEN_VAR){
        var_map[root.data._TOKEN_VALUE] = 0;
    }


    for(size_t i = 0; i < root.childs.size(); i++){
        execute(root.childs[i]);
    }
}

int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "NO, input file" << "\n";
        return 0;
    }

    Lexer lex;

    vector<meow_line> _prog_lines = file_to_vect(argv[1]);
    lex._rt_None_tokenize(_prog_lines);
    std::vector<Token> tokenized_list = lex._rt_token_gettokenizedlist();

    // VariableMap varmap;

    // Token empty;
    // empty._TOKEN_LINE = "";
    // empty._TOKEN_LINE_NUMBER = 0;
    // empty._TOKEN_TYPE = _TOKEN_NULL;
    // empty._TOKEN_VALUE = "";

    // for(size_t i = 0; i < tokenized_list.size(); i++){
    //     if(tokenized_list[i]._TOKEN_TYPE == _TOKEN_VAR){
    //         varmap.add_var(tokenized_list[i], empty);
    //     }
    // }

    Parser parser;
    parser.setProg_Tokens(tokenized_list);
    Tree AST = parser.Parse();

    // This is for debuging purposes remove it when actually compiling.
    std::cout << "=================DEBUG==================\n";
    
    for(size_t i = 0; i < tokenized_list.size(); i ++){
        std:: cout << "Token Type = " << tokenized_list[i]._TOKEN_TYPE << "\t\t" << "Token value = " << tokenized_list[i]._TOKEN_VALUE << "\t\t" << "Line Number = " << tokenized_list[i]._TOKEN_LINE_NUMBER << "\n";
    }

    // print the ast tree
    AST._rt_None_print_tree();
    
    std::cout << "\n================ACTUAL EXECUTION============\n";
    
    execute(AST);

    return 0;
}
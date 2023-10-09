#include <iostream>
#include <vector>
#include <unordered_map>
#include <string.h>

#include "include/core.hpp"
#include "include/lexer.hpp"
#include "include/token.hpp"
#include "include/tree.hpp"
#include "include/parser.hpp"

using std::vector;
using std::cout;
using std::string;

std::unordered_map<string, int> var_map;

void execute(Tree root){
    
    switch(root.data._TOKEN_TYPE){

        case _TOKEN_VAR:

            if(var_map.find(root.data._TOKEN_VALUE) == var_map.end()){
                var_map[root.data._TOKEN_VALUE] = 0;
            }
            break;

        case _TOKEN_EQU:

            var_map[root.parent->data._TOKEN_VALUE] = std::stoi(root.childs[0].data._TOKEN_VALUE);
            break;

        case _TOKEN_SHOW:

            if(root.childs[0].data._TOKEN_TYPE == _TOKEN_INT)
                std::cout << var_map[root.childs[0].data._TOKEN_VALUE] << "\n";
            else if(root.childs[0].data._TOKEN_TYPE == _TOKEN_STRING)
                std::cout << root.childs[0].data._TOKEN_VALUE << "\n";

        default:
            break;
    };

    for(Tree i : root.childs){
        execute(i);
    }
}

int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "No, input file" << "\n";
        return 0;
    }

    // DEBUG is a macro sent through the command line.

    Lexer lex;

    vector<meow_line> _prog_lines = file_to_vect(argv[1]);
    lex.tokenize(_prog_lines);
    std::vector<Token> tokenized_list = lex.get_tokenized_vector();

    Parser parser;
    parser.setToken(tokenized_list);
    Tree AST = parser.parse();

    // This is for debuging purposes remove it when actually compiling.

    #ifdef DEBUG

        std::cout << "=====================[ DEBUG ]======================\n";
    
        for(size_t i = 0; i < tokenized_list.size(); i ++){
            std:: cout << "Token Type = " << tokenized_list[i]._TOKEN_TYPE << "\t\t" << "Token value = " << tokenized_list[i]._TOKEN_VALUE << "\t\t" << "Line Number = " << tokenized_list[i]._TOKEN_LINE_NUMBER << "\n";
        }

        std::cout << "===================[ VAR MAP ] =====================\n";
        for(auto const &pair: var_map){
            std::cout << pair.first << " = " << pair.second << "\n";
        }
        // print the ast tree
        //std::cout << "\n Tree -> \n";
        AST.print_tree();
    
        std::cout << "\n===============[ ACTUAL EXECUTION ]============\n";

    #endif
    
    //execute(AST);


    return 0;
}
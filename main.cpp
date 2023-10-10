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

size_t solveExpression(Tree root){
    Tree child_tok = root;
    
    if(child_tok.data._TOKEN_TYPE == _TOKEN_PLUS){
        return solveExpression(root.childs[0]) + solveExpression(root.childs[1]);
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MUL){
        return solveExpression(root.childs[0]) * solveExpression(root.childs[1]);
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MINUS){
        return solveExpression(root.childs[0]) - solveExpression(root.childs[1]);
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_DIV){
        return solveExpression(root.childs[0]) / solveExpression(root.childs[1]);
    }
    else{
        return std::stoi(child_tok.data._TOKEN_VALUE);
    }
}

void executeVar(Tree root){
    Token var = root.data;
    Tree child_tok = root.childs[0].data;

    std::cout << var._TOKEN_VALUE << "\n";
    if(child_tok.data._TOKEN_TYPE == _TOKEN_EQU){
        std::cout << solveExpression(child_tok.childs[0]);
    }
}

void executeShow(Tree root){
    Tree child_tok = root.childs[0];

    if(child_tok.data._TOKEN_TYPE == _TOKEN_STRING){
        std::string data = root.childs[0].data._TOKEN_VALUE;
        std::string fdata = "";

        for(char I : data){
            if(I != '"'){
                fdata += I;
            }
        }

        std::cout << fdata << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_VAR){
        std::cout << var_map[child_tok.data._TOKEN_VALUE] << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_INT){
        std::cout << solveExpression(child_tok) << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_PLUS){
        std::cout << solveExpression(child_tok) << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_DIV){
        std::cout << solveExpression(child_tok) << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MUL){
        std::cout << solveExpression(child_tok) << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MINUS){
        std::cout << solveExpression(child_tok) << "\n";
    }
}

// Improve this
void execute(Tree root){
    if(root.data._TOKEN_TYPE == _TOKEN_SHOW){
        executeShow(root);
    }
    else if(root.data._TOKEN_TYPE == _TOKEN_VAR){
        executeVar(root);
    }
}

int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "No, input file" << "\n";
        return 0;
    }

    // DEBUG is a macro sent through the command line.

    vector<meow_line> _prog_lines = file_to_vect(argv[1]);
    
    Lexer lex;
    Parser parser;
    std::vector<Token> tokenized_vector;
    Tree AST;

    for(meow_line line : _prog_lines){

        tokenized_vector = lex.tokenize(line);

        AST = parser.parse(tokenized_vector);


        if(DEBUG){

            std::cout << "\nLine - " << line.line << "\n";

            std::cout << "=====================[ DEBUG ]======================\n";

            for(size_t i = 0; i < tokenized_vector.size(); i ++){
                std:: cout << "Token Type = " << tokenized_vector[i]._TOKEN_TYPE << "\t\t" << "Token value = " << tokenized_vector[i]._TOKEN_VALUE << "\t\t" << "Line Number = " << tokenized_vector[i]._TOKEN_LINE_NUMBER << "\n";
            }

            std::cout << "===================[ VAR MAP ] =====================\n";
            for(auto const &pair: var_map){
                std::cout << pair.first << " = " << pair.second << "\n";
            }
    
            std::cout << "================[ TREE ]===================\n";

            AST.print_tree();

            std::cout << std::endl;
            std::cout << "===============[ ACTUAL EXECUTION ]============\n";
        }
        execute(AST.childs[0]);

        //std::cout << "Done\n";
    }


    return 0;
}
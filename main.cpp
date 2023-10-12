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

std::unordered_map<string, long double> var_map;

long double solveExpression(Tree root){
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
        return std::stold(child_tok.data._TOKEN_VALUE);
    }
}

long double executeVar(Tree root){
    Token var = root.data;
    Tree child_tok = root.childs[0];
    Tree op_Token = root.childs[0].childs[0];
    long double expression_output;
    //var_map[var._TOKEN_VALUE] = 0;

    // std::cout << var._TOKEN_VALUE << "\n";
    // std::cout << child_tok.data._TOKEN_VALUE << "\n";
    // std::cout << root.childs[0].childs[0].data._TOKEN_VALUE << "\n";

    if(child_tok.data._TOKEN_TYPE == _TOKEN_EQU){

        if(op_Token.data._TOKEN_TYPE == _TOKEN_INT){
            expression_output = std::stold(op_Token.data._TOKEN_VALUE);
            var_map[var._TOKEN_VALUE] = expression_output;
        }

        else if(op_Token.data._TOKEN_TYPE == _TOKEN_PLUS){
            expression_output = solveExpression(op_Token);
            var_map[var._TOKEN_VALUE] = expression_output;
        }

        else if(op_Token.data._TOKEN_TYPE == _TOKEN_MINUS){
            expression_output = solveExpression(op_Token);
            var_map[var._TOKEN_VALUE] = expression_output;
        }

        else if(op_Token.data._TOKEN_TYPE == _TOKEN_DIV){
            expression_output = solveExpression(op_Token);
            var_map[var._TOKEN_VALUE] = expression_output;
        }

        else if(op_Token.data._TOKEN_TYPE == _TOKEN_MUL){
            expression_output = solveExpression(op_Token);
            var_map[var._TOKEN_VALUE] = expression_output;
        }

        else if(op_Token.data._TOKEN_TYPE == _TOKEN_VAR){
            var_map[var._TOKEN_VALUE] = executeVar(op_Token);
        }
    }

    return expression_output;
}

void executeShow(Tree root){
    if(root.childs[0].data._TOKEN_TYPE == _TOKEN_SEMI_COL) return;

    Tree child_tok = root.childs[0];

    if(child_tok.data._TOKEN_TYPE == _TOKEN_STRING){
        std::string data = root.childs[0].data._TOKEN_VALUE;
        std::string fdata = "";

        for(char I : data){
            if(I != '"'){
                fdata += I;
            }
        }

        std::cout << fdata;
        
        executeShow(child_tok);
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_VAR){
        std::cout << var_map[child_tok.data._TOKEN_VALUE] << "\n";
        //std::cout << child_tok.data._TOKEN_VALUE;
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_BEERUS){
        std::cout << child_tok.data._TOKEN_VALUE << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_AYO){
        std::cout << child_tok.data._TOKEN_VALUE << "\n";
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MEOWTH){
        std::cout << child_tok.data._TOKEN_VALUE << "\n"; 
    }

    else if(child_tok.data._TOKEN_TYPE == _TOKEN_PIKA){
        std::cout << child_tok.data._TOKEN_VALUE << "\n"; 
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

            AST.print_tree(0);

            std::cout << std::endl;
            std::cout << "===============[ ACTUAL EXECUTION ]============\n";
        }
        execute(AST.childs[0]);

        //std::cout << "Done\n";
    }


    return 0;
}
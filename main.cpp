#include <iostream>
#include <vector>
#include <unordered_map>
#include <string.h>

#include "include/core.hpp"
#include "include/lexer.hpp"
#include "include/token.hpp"
#include "include/tree.hpp"
#include "include/parser.hpp"
#include "include/interpreter.hpp"
#include "include/vm.hpp"
#include "include/error.hpp"

using std::vector;
using std::cout;
using std::string;

int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "No, input file" << "\n";
        return 0;
    }

    // DEBUG is a macro sent through the command line.
    vector<meow_line> program_lines = file_to_vect(argv[1]);
    
    Lexer lex;
    Parser parser;
    Tree AST;
    Interpreter interpreter;
    
    std::vector<Token> tokenized_vector;

    for(meow_line line : program_lines){

        tokenized_vector = lex.tokenize(line);
        //checkSyntax(tokenized_vector);
        AST = parser.parse(tokenized_vector);
        interpreter.convertToByteCode(AST.get_child(0));

        #ifdef DEBUG

            std::cout << "\nLine - " << line.line << "\n";

            std::cout << "=====================[ TOKENS ]======================\n";

            for(size_t i = 0; i < tokenized_vector.size(); i ++){
                std:: cout << "Token Type = " << tokenized_vector[i]._TOKEN_TYPE << "\t\t" << "Token value = " << tokenized_vector[i]._TOKEN_VALUE << "\t\t" << tokenized_vector[i]._TOKEN_LINE << "\t\t" << "Line Number = " << tokenized_vector[i]._TOKEN_LINE_NUMBER << " INDENTATION = " << tokenized_vector[i]._INDENTATION << "\n";
            }
    
            std::cout << "================[ PARSE TREE ]===================\n";
            AST.print_tree(0);

            std::cout << std::endl;

            std::cout << "===============[ BYTE CODE ]============\n";
            showByteCode();
            std::cout << "===============[ BYTE CODE EXECUTION ]============\n";
            
        #endif
    }
    run();
    
    return 0;
}
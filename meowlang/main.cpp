#include <iostream>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <string>

#include "../include/core.hpp"
#include "../include/lexer.hpp"
#include "../include/token.hpp"
#include "../include/compiler.hpp"
#include "../include/internals/mewcore_ast.hpp"
#include "../parser/parser.hpp"
#include "../include/vm.hpp"
#include "../include/error.hpp"

using std::vector;
using std::cout;
using std::string;

#define DEBUG

int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "No, input file" << "\n";
        return 0;
    }

    vector<meow_line> program_lines = file_to_vect(argv[1]);
    
    // meowlang pipeline
    Lexer lex;
    //Parser parser;
    //Tree AST;
    //Compiler compiler;
    
    std::vector<Token> tokenized_vector;
    //std::vector<bytecode> generated_bytecode;

    for(meow_line line : program_lines){

        for(const Token &toks : lex.tokenize(line)) tokenized_vector.push_back(toks);
        //AST = parser.parse(tokenized_vector);
        //compiler.compile(generated_bytecode, AST.get_child(0));
    }
    tokenized_vector.push_back(makeToken(_TOKEN_EOT, "end of token", "none", 0));
    
    #ifdef DEBUG
    std::cout << "=====================[ TOKENS ]======================\n";
    for(size_t i = 0; i < tokenized_vector.size(); i ++){
        std:: cout << "Token Type = " << token_names_for_loging[tokenized_vector[i]._TOKEN_TYPE] << "\t\t\t" << "Token value = " << tokenized_vector[i]._TOKEN_VALUE << "\t\t\t" << "Token Line - " << tokenized_vector[i]._TOKEN_LINE << "\t\t\t" << "Line Number - " << tokenized_vector[i]._TOKEN_LINE_NUMBER << "\t\t\t" << " INDENTATION - " << tokenized_vector[i]._INDENTATION << "\n";
    }
    std::cout << "================[ PARSE TREE ]===================\n";
    //AST.print_tree(0);
    std::cout << std::endl;
    std::cout << "===============[ BYTE CODE ]============\n";
    //showByteCode();
    std::cout << "===============[ BYTE CODE EXECUTION ]============\n";
    #endif
    #undef DEBUG

    //std::vector<Token> extoks = { makeToken(_TOKEN_VAR, "x", "none", 0, 0),  makeToken(_TOKEN_EQU, "=", "none", 0, 0),  makeToken(_TOKEN_FLOAT, "1.232", "none", 0, 0),  makeToken(_TOKEN_SEMI_COL, ";", "none", 0, 0)};

    mod_ty *module = (mod_ty *) parse(tokenized_vector, File_Rule);

    // if(module == NULL)
    // {
    //     std::cout << "Failed to parser\n";
    //     return 0;
    // }

    display(module->v.Module.body);

    // std::cout << module->v.Module.body[0]->v.Assign.body->v.NameExpr.target->v.Name.id->data.Char.val << "\n";
    // std::cout << module->v.Module.body[0]->v.Assign.body->v.NameExpr.value->v.Const.value->data.Float.val << "\n";
    // std::cout << module->v.Module.body[0]->v.Assign.body->v.NameExpr.value->v.Const.value->data.Integer.val << "\n";
    // std::cout << module->v.Module.body[0]->v.Assign.body->v.NameExpr.value->v.Const.value->data.Char.val << "\n";
    
    
    // compile the tokens to bytecode and send the bytecode to VM

    std::cout << "Parsed sucessfully\n";
    return 0;
}
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
#include "../include/code.hpp"
#include "../parser/parser.hpp"
#include "../include/vm.hpp"
#include "../include/error.hpp"
#include "../include/byteblocks.hpp"

using std::vector;
using std::cout;
using std::string;

//#define DEBUG
//#undef DEBUG

void printBlock(Block *block)
{
    std::cout << "BLOCK ID -> " << block->id << "\n";

    for(bytecode &bc : block->bytes)
    {
        std::cout << "Op : " << opcodes_string[(int)bc.op] << "\t" << "Arg : " << bc.arg << "\n";
    }

    for(Block *b : block->block)
    {
        printBlock(b);
    }
}


int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "No, input file" << "\n";
        return 0;
    }

    //vector<meow_line> essential_lines = file_to_vect("essential.meow");
    vector<meow_line> program_lines = file_to_vect(argv[1]);

    // meowlang pipeline
    Lexer lex;
    //Parser parser;
    //Tree AST;
    //Compiler compiler;
    
    std::vector<Token> tokenized_vector;
    //std::vector<bytecode> generated_bytecode;

    // tokenize essentials file
    // for(meow_line line : essential_lines)
    // {
    //     for(const Token &toks : lex.tokenize(line))
    //     {
    //         tokenized_vector.push_back(toks);
    //     }
    // }

    for(meow_line line : program_lines){

        for(const Token &toks : lex.tokenize(line))
        {
            tokenized_vector.push_back(toks);
        }
        //AST = parser.parse(tokenized_vector);
        //compiler.compile(generated_bytecode, AST.get_child(0));
    }
    tokenized_vector.push_back(makeToken(_TOKEN_EOT, "end of token", "none", 0));
    
    #ifdef DEBUG
    std::cout << "=====================[ TOKENS ]======================\n";
    for(size_t i = 0; i < tokenized_vector.size(); i ++){
        std:: cout << "Token Type = " << token_names_for_loging[tokenized_vector[i]._TOKEN_TYPE] << "\t\t\t" << "Token value = " << tokenized_vector[i]._TOKEN_VALUE << "\t\t\t" << "Token Line - " << tokenized_vector[i]._TOKEN_LINE << "\t\t\t" << "Line Number - " << tokenized_vector[i]._TOKEN_LINE_NUMBER << "\t\t\t" << " INDENTATION - " << tokenized_vector[i]._INDENTATION << "\n";
    }
    std::cout << "========================================================\n";
    #endif

    //std::vector<Token> extoks = { makeToken(_TOKEN_VAR, "x", "none", 0, 0),  makeToken(_TOKEN_EQU, "=", "none", 0, 0),  makeToken(_TOKEN_FLOAT, "1.232", "none", 0, 0),  makeToken(_TOKEN_SEMI_COL, ";", "none", 0, 0)};

    Module *module = (Module *) parse(tokenized_vector, File_Rule);
    #ifdef DEBUG
    std::cout << "Parsed sucessfully\n";
    #endif
    //return 0;
    
    Block *byteblock;
    //return 0;
    if(module)
    {
        byteblock = compile(module);

        #ifdef DEBUG
        printBlock(byteblock);
        #endif

        Interpreter *interpreter = new Interpreter(byteblock);

        interpreter->Execute();
        
    }

    // TODO:: free all the heap allocated class that you made in parse method

    #undef DEBUG

    return 0;
}
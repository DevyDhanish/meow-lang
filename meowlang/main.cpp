#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>

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

#define DEBUG
//#undef DEBUG

void val(uint64_t obj)
{
    Integer *i_obj = reinterpret_cast<Integer *>(obj);
    Float *f_obj = reinterpret_cast<Float *>(obj);
    String *s_obj = reinterpret_cast<String *>(obj);
    Var *v_obj = reinterpret_cast<Var *>(obj);

    if(!(i_obj && f_obj && s_obj && v_obj)) return;

    switch (((MeowObject *)obj)->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj:
        std::cout << ((Integer *)obj)->value;
        break;
    case MEOWOBJECTKIND::Meow_FloatObj:
        std::cout << ((Float *)obj)->value;
        break;
    case MEOWOBJECTKIND::Meow_StringObj:
        std::cout << ((String *)obj)->value;
        break;
    case MEOWOBJECTKIND::Meow_VarObj:
        std::cout << ((Var *)obj)->value;
        break;

    case MEOWOBJECTKIND::Meow_ArrayObj:
        ((ArrayObj *)obj)->onShow();
        break;
    
    default:
        break;
    }
}

void printBlock(Block *block)
{
    std::cout << "BLOCK ID -> " << block->id << "\n";

    for(bytecode &bc : block->bytes)
    {
        std::cout << std::setw(5) << std::left << "Op : " << std::setw(15) << std::left << opcodes_string[(int)bc.op] << std::setw(5) << std::left << "Arg : " << "<0x"<< std::hex << bc.arg <<">" << std::setw(4) << std::left << "\t";
        if(bc.arg > 1000) val(bc.arg);
        std::cout << "\n";
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

    if(!isMeowFile(argv[1]))
    {
        std::cout << "Wrong file type, make sure the files ends with `.meow`\n";
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
        std::cout << std::setw(10) << std::left << "Token Type = " << token_names_for_loging[tokenized_vector[i]._TOKEN_TYPE] << "\t" << std::setw(20) << std::left << "Token value = " << tokenized_vector[i]._TOKEN_VALUE << std::setw(10) << std::left << "\t" << "Token Line - " << tokenized_vector[i]._TOKEN_LINE << std::setw(20) << std::left << "Line Number - " << tokenized_vector[i]._TOKEN_LINE_NUMBER << "\n";
    }
    std::cout << "=======================[ PARSING ]===========================\n";
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
        std::cout << "============================[ BYTEBLOCKS ]=======================\n";
        printBlock(byteblock);
        #endif

        Interpreter *interpreter = new Interpreter(byteblock);


        #ifdef DEBUG
        std::cout << "======================[ EXECUTION ]======================\n";
        #endif

        interpreter->Execute();
        
    }

    // TODO:: free all the heap allocated class that you made in parse method

    #undef DEBUG

    return 0;
}
#include "../include/parser.hpp"
#include "../include/tree.hpp"
#include "../include/token.hpp"
#include "../include/core.hpp"

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

void Parser::advance(){
    if(this->counter < this->progToken.size()){
        this->current_token = this->progToken[this->counter];
        this->counter++;
    }
    else{
        this->current_token = makeToken(_TOKEN_EMPTY, "empty", "empty", 0);
    }
}

Tree Parser::parseEqu(){
    Tree equ(this->current_token);

    advance();

    switch(this->current_token._TOKEN_TYPE){
        case _TOKEN_STRING:
            equ.add_child(Tree(this->current_token));
            break;
        case _TOKEN_INT:
            equ.add_child(Tree(this->current_token));
            break;
        default:
            std::cout << "alsdfj" ;
    }

    return equ;
}

Tree Parser::parseVar(){
    Tree var(this->current_token);

    advance();

    switch(this->current_token._TOKEN_TYPE){
        case _TOKEN_EQU:
            var.add_child(parseEqu());
            break;
        case _TOKEN_SEMI_COL:
            break;
        default:
            break;
    }

    return var;
}

Tree Parser::parseShow(){
    Tree show(this->current_token);
    advance();
    switch(this->current_token._TOKEN_TYPE){
        case _TOKEN_VAR:
            show.add_child(parseVar());
            break;
        case _TOKEN_INT:
            show.add_child(Tree(this->current_token));
            break;
        case _TOKEN_STRING:
            show.add_child(Tree(this->current_token));
            break;
    }
    return show;
}

Tree Parser::parse(){
    Tree main(makeToken(_TOKEN_START, START_NODE, START_NODE, 0));

    advance();
    while(this->current_token._TOKEN_TYPE != _TOKEN_EMPTY){
        
        switch (this->current_token._TOKEN_TYPE)
        {
            case _TOKEN_VAR:
                main.add_child(parseVar());
                break;
            
            case _TOKEN_SHOW:
                main.add_child(parseShow());
                break;
        }

        advance();
    }

    return main;
}
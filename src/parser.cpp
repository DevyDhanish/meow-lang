#include "../include/parser.hpp"
#include "../include/tree.hpp"
#include "../include/token.hpp"
#include "../include/core.hpp"

#include <vector>
#include <iostream>

void Parser::advance(){
    if(this->counter < this->progToken.size()){
        this->current_token = this->progToken[this->counter];
        this->counter++;
    }
    else{
        this->current_token = makeToken(_TOKEN_EMPTY, "", "", 0);
    }
}

Tree Parser::parseEqu(){
    Tree equ(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING){
        equ.add_child(parseStr());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        equ.add_child(parseInt());
    }

    return equ;
}

Tree Parser::parseVar(){
    Tree var(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return var;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_EQU){
        // parse assignment
        var.add_child(parseEqu());

        return var;
    }

    else {
        std::cout << "Syntax error : in line " << this->current_token._TOKEN_LINE_NUMBER << " - " << this->current_token._TOKEN_LINE << "\n";
        exit(0);
    }
}

Tree Parser::parseStr(){
    Tree str(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return str;
    }

    return str;
}

Tree Parser::parseInt(){
    Tree _int(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return _int;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_DIV){
        Tree div(this->current_token);
        div.add_child(_int);
        advance();
        div.add_child(parseInt());

        return div;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_MUL){
        Tree mul(this->current_token);
        mul.add_child(_int);
        advance();
        mul.add_child(parseInt());

        return mul;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_PLUS){
        Tree plus(this->current_token);
        plus.add_child(_int);
        advance();
        plus.add_child(parseInt());

        return plus;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_MINUS){
        Tree minus(this->current_token);
        minus.add_child(_int);
        advance();
        minus.add_child(parseInt());

        return minus;
    }
    else{
        std::cout << "Syntax error : in line " << this->current_token._TOKEN_LINE_NUMBER << " - " << this->current_token._TOKEN_LINE << "\n";
        exit(0);
    }

    //return _int;
}

Tree Parser::parseBee(){
    Tree bee(makeToken(_TOKEN_BEERUS, BEERUS, "beerus", 0));

    std::string current_line = this->current_token._TOKEN_LINE;
    size_t current_line_number = this->current_token._TOKEN_LINE_NUMBER;

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return bee;
    }

    else{
        std::cout << "Syntax error: in line `" << current_line << "` : line number: " << current_line_number << "\n";
        exit(0);
    }
}

Tree Parser::parseMeo(){
    Tree meo(makeToken(_TOKEN_MEOWTH, MEOWTH, "meowth", 0));

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return meo;
    }

    return meo;
}

Tree Parser::parsePika(){
    Tree meo(makeToken(_TOKEN_PIKA, PIKA, "pika", 0));

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return meo;
    }

    return meo;
}

Tree Parser::parseAyo(){
    Tree ayo(makeToken(_TOKEN_AYO, AYO, "ayo", 0));

    advance();


    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        return ayo;
    }

    return ayo;
}

Tree Parser::parseShow(){
    Tree show(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
        show.add_child(parseVar());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_BEERUS){
        show.add_child(parseBee());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_MEOWTH){
        show.add_child(parseMeo());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_PIKA){
        show.add_child(parsePika());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_AYO){
        show.add_child(parseAyo());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_STRING){
        show.add_child(parseStr());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        show.add_child(parseInt());
    }

    return show;
}

Tree Parser::parse(std::vector<Token> prog_token){
    this->counter = 0;
    Tree main(makeToken(_TOKEN_START, START_NODE, "", 0));
    
    this->progToken = prog_token;
    advance();

    while(this->counter < prog_token.size()){

        if(this->current_token._TOKEN_TYPE == _TOKEN_SHOW){
            main.add_child(parseShow());
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
            main.add_child(parseVar());
        }

    }

    this->progToken.clear();

    return main;
}
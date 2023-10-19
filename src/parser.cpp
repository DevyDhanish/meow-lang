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
        this->current_token = makeToken(_TOKEN_EMPTY, "", "", 0, 0);
    }
}

Tree Parser::parseEqu(){
    Tree equ(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING){
        equ.add_child(parseStr());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        equ.add_child(parseAddSub());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
        equ.add_child(parseAddSub());
    }

    return equ;
}

Tree Parser::parseAddSub(){
    Tree left = parseMulDiv();

    while(this->current_token._TOKEN_TYPE == _TOKEN_PLUS || this->current_token._TOKEN_TYPE == _TOKEN_MINUS){
        Token op_token = this->current_token;
        advance();
        Tree right = parseMulDiv();

        Tree expression(op_token);
        expression.add_child(left);
        expression.add_child(right);

        left = expression;
    }


    return left;
}

Tree Parser::parseMulDiv(){
    Tree left = parseInt();

    while(this->current_token._TOKEN_TYPE == _TOKEN_MUL || this->current_token._TOKEN_TYPE == _TOKEN_DIV){
        Token op_token = this->current_token;
        advance();
        Tree right = parseInt();

        Tree expression(op_token);
        expression.add_child(left);
        expression.add_child(right);
        left = expression;
    }


    return left;
}

Tree Parser::parseVar(){
    Tree var(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL || this->current_token._TOKEN_TYPE == _TOKEN_COLON){
        //var.add_child(this->current_token);
        return var;
    }

    // else if (this->current_token._TOKEN_TYPE == _TOKEN_PLUS || this->current_token._TOKEN_TYPE == _TOKEN_MINUS ||
    //          this->current_token._TOKEN_TYPE == _TOKEN_MUL || this->current_token._TOKEN_TYPE == _TOKEN_DIV) {
    //     var.add_child(parseAddSub()); // Continue parsing the expression.
    //     return var;
    // }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_EQU){
        var.add_child(parseEqu());
        //return var;
    }


    return var;
}

Tree Parser::parseStr(){
    Tree str(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL || this->current_token._TOKEN_TYPE == _TOKEN_COLON){
        str.add_child(this->current_token);
        return str;
    }

    return str;
}

Tree Parser::parseShowStr(){
    Tree str(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        str.add_child(this->current_token);
        return str;
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
        str.add_child(parseVar());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        str.add_child(parseAddSub());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_STRING){
        str.add_child(parseShowStr());
    }
    else{
        std::cout << "Syntax error : in line " << this->current_token._TOKEN_LINE_NUMBER << " - " << this->current_token._TOKEN_LINE << "\n";
        exit(0);
    }

    return str;
}

Tree Parser::parseInt(){
    Tree _int(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL || this->current_token._TOKEN_TYPE == _TOKEN_COLON){
        return _int;
    }

    return _int;
}

Tree Parser::parseBee(){
    Tree bee(makeToken(_TOKEN_BEERUS, BEERUS, "beerus", 0, 0));

    std::string current_line = this->current_token._TOKEN_LINE;
    size_t current_line_number = this->current_token._TOKEN_LINE_NUMBER;

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        bee.add_child(this->current_token);
        return bee;
    }

    else{
        std::cout << "Syntax error: in line `" << current_line << "` : line number: " << current_line_number << "\n";
        exit(0);
    }
}

Tree Parser::parseMeo(){
    Tree meo(makeToken(_TOKEN_MEOWTH, MEOWTH, "meowth", 0, 0));

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        meo.add_child(this->current_token);
        return meo;
    }

    return meo;
}

Tree Parser::parsePika(){
    Tree pika(makeToken(_TOKEN_PIKA, PIKA, "pika", 0, 0));

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        pika.add_child(this->current_token);
        return pika;
    }

    return pika;
}

Tree Parser::parseAyo(){
    Tree ayo(makeToken(_TOKEN_AYO, AYO, "ayo", 0, 0));

    advance();


    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        ayo.add_child(this->current_token);
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
        show.add_child(parseShowStr());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        show.add_child(parseAddSub());
    }

    return show;
}

Tree Parser::parseIf(){

    size_t ifCounter = 1;
    std::vector<std::vector<Token>> ifTokens;
    std::vector<Token> toks;
    Tree _if(this->current_token);

    while(ifCounter < this->progToken.size())
    {
        if(this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_LESSTHAN    ||  
        this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_GREATERTHAN    ||
        this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_LESSEQU        ||
        this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_GREATEREQU     ||
        this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_EQUALSTO       ||
        this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_NOTEQUALS)
        {
            ifTokens.push_back(std::vector<Token> {this->progToken[ifCounter]});
            ifTokens.push_back(toks);
            toks.clear();
        }

        else if(this->progToken[ifCounter]._TOKEN_TYPE == _TOKEN_COLON){
            ifTokens.push_back(toks);
            toks.clear();
            break;
        }

        else { 
            toks.push_back(this->progToken[ifCounter]);
        }

        ifCounter++;
    };

    for(std::vector<Token> tokens_of_if : ifTokens){

        // for(Token i : tokens_of_if){
        //     std::cout << i._TOKEN_VALUE;
        // }
        // std::cout << "\n";

        
        if(
            tokens_of_if[0]._TOKEN_TYPE == _TOKEN_EQUALSTO      ||
            tokens_of_if[0]._TOKEN_TYPE == _TOKEN_NOTEQUALS     ||
            tokens_of_if[0]._TOKEN_TYPE == _TOKEN_LESSTHAN      ||
            tokens_of_if[0]._TOKEN_TYPE == _TOKEN_GREATERTHAN   ||
            tokens_of_if[0]._TOKEN_TYPE == _TOKEN_LESSEQU       ||
            tokens_of_if[0]._TOKEN_TYPE == _TOKEN_GREATEREQU    
            ){
            Tree equ_to(tokens_of_if[0]);
            _if.add_child(equ_to);
        }

        else if(tokens_of_if[0]._TOKEN_TYPE == _TOKEN_INT){
            this->progToken = tokens_of_if;
            this->counter = 0;
            advance();
            _if.add_child(parseAddSub());
        }

        else if(tokens_of_if[0]._TOKEN_TYPE == _TOKEN_VAR){
            this->progToken = tokens_of_if;
            this->counter = 0;
            advance();
            _if.add_child(parseVar());
        }

        else if(tokens_of_if[0]._TOKEN_TYPE == _TOKEN_STRING){
            this->progToken = tokens_of_if;
            this->counter = 0;
            advance();
            _if.add_child(parseStr());
        }
    }

    return _if;
}

Tree Parser::parseElse(){
    Tree _else(this->current_token);
    return _else;
}

Tree Parser::parseWhile(){
    Tree _while(this->current_token);
    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        _while.add_child(parseAddSub());
    }

    return _while;
}

Tree Parser::parse(std::vector<Token> prog_token){
    this->counter = 0;
    Tree main(makeToken(_TOKEN_START, START_NODE, "", 0, 0));
    
    this->progToken = prog_token;
    advance();

    while(this->counter < prog_token.size()){

        if(this->current_token._TOKEN_TYPE == _TOKEN_SHOW){
            main.add_child(parseShow());
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
            main.add_child(parseVar());
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_IF || this->current_token._TOKEN_TYPE == _TOKEN_ELIF){
            main.add_child(parseIf());
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_ELSE){
            main.add_child(parseElse());
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_WHILE){
            main.add_child(parseWhile());
        }
        this->counter++;
    }

    this->progToken.clear();

    return main;
}
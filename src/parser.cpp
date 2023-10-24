#include "../include/parser.hpp"
#include "../include/tree.hpp"
#include "../include/token.hpp"
#include "../include/core.hpp"
#include "../include/error.hpp"

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

void Parser::changeContext(Contenxt_t newContext)
{
    this->current_context = newContext;
}

Token Parser::lookAhead()
{
    if(this->counter < this->progToken.size())
    {
        return this->progToken[this->counter];
    }
    else
    {
        return makeToken(_TOKEN_EMPTY, "", "", 0, 0);
    }
}

bool find(std::vector<TOKEN_T> pool, TOKEN_T target)
{
    if(std::find(pool.begin(), pool.end(), target) == pool.end()){
        return false;
    }else{
        return true;
    }
}

Tree Parser::parseTake(){
    Tree take(this->current_token);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        take.add_child(parseStr());
    }

    return take;
}

Tree Parser::parseEqu(){
    Tree equ(this->current_token);

    // std::vector<TOKEN_T> valid_next_tokens;

    // if(this->current_context == _C_ASSIGNMNET)
    // {
    //     valid_next_tokens = {_TOKEN_VAR, _TOKEN_INT, _TOKEN_STRING};
    // }

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);


    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING){
        equ.add_child(parseStr());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        changeContext(_C_EXPR);
        equ.add_child(parseAddSub());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
        changeContext(_C_EXPR);
        equ.add_child(parseAddSub());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_TAKE){
        equ.add_child(parseTake());
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

    while(this->current_token._TOKEN_TYPE == _TOKEN_MUL || this->current_token._TOKEN_TYPE == _TOKEN_DIV || this->current_token._TOKEN_TYPE == _TOKEN_MOD){
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

    // std::vector<TOKEN_T> valid_next_tokens;

    // if(this->current_context == _C_ASSIGNMNET)
    // {
    //     valid_next_tokens = {_TOKEN_EQU};
    // }

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL || this->current_token._TOKEN_TYPE == _TOKEN_COLON){
        var.add_child(this->current_token);
        return var;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_EQU){
        var.add_child(parseEqu());
    }

    return var;
}

Tree Parser::parseStr(){
    Tree str(this->current_token);

    // std::vector<TOKEN_T> valid_next_tokens;

    // if(this->current_context == _C_ASSIGNMNET)
    // {
    //     valid_next_tokens = {_TOKEN_SEMI_COL};
    // }

    // if(this->current_context == _C_IF_STMT || this->current_context == _C_LOOP_STMT)
    // {
    //     valid_next_tokens = {_TOKEN_COLON, _TOKEN_EQUALSTO, _TOKEN_NOTEQUALS, _TOKEN_LESSTHAN, _TOKEN_GREATERTHAN, _TOKEN_LESSEQU, _TOKEN_GREATEREQU};
    // }

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);


    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL || this->current_token._TOKEN_TYPE == _TOKEN_COLON){
        str.add_child(this->current_token);
        return str;
    }

    return str;
}

Tree Parser::parseNewLine()
{
    // if(this->current_context == _C_OUTPUT)
    // {
    //     std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_STRING, _TOKEN_INT, _TOKEN_VAR, _TOKEN_NEW_LINE, _TOKEN_BEERUS, _TOKEN_MEOWTH, _TOKEN_PIKA, _TOKEN_MEOWTH, _TOKEN_SEMI_COL};

    //     if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);
    // }

    Tree nl(this->current_token);
    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        nl.add_child(this->current_token);
        return nl;
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR)
    {
        nl.add_child(parseShowVar());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT)
    {
        nl.add_child(parseAddSub());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        nl.add_child(parseShowStr());
    }

    return nl;
}

Tree Parser::parseShowVar()
{
    Tree var(this->current_token);

    // if(this->current_context == _C_OUTPUT)
    // {
    //     std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_STRING, _TOKEN_INT, _TOKEN_VAR, _TOKEN_NEW_LINE, _TOKEN_BEERUS, _TOKEN_MEOWTH, _TOKEN_PIKA, _TOKEN_SEMI_COL};

    //     if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);
    // }

    advance();
    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        var.add_child(parseShowStr());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR)
    {
        var.add_child(parseShowVar());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        var.add_child(parseAddSub());
    }

    return var;
}

Tree Parser::parseShowStr(){
    Tree str(this->current_token);

    // if(this->current_context = _C_OUTPUT)
    // {
    //     std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_STRING, _TOKEN_INT, _TOKEN_VAR, _TOKEN_NEW_LINE, _TOKEN_BEERUS, _TOKEN_MEOWTH, _TOKEN_PIKA, _TOKEN_SEMI_COL};

    //     if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

    // }

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL)
    {
        str.add_child(this->current_token);
        return str;
    }
    if(this->current_token._TOKEN_TYPE == _TOKEN_NEW_LINE)
    {
        str.add_child(parseNewLine());
        return str;
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
        str.add_child(parseShowVar());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT){
        str.add_child(parseAddSub());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_STRING){
        str.add_child(parseShowStr());
    }

    return str;
}

Tree Parser::parseInt(){
    Tree _int(this->current_token);

    // std::vector<TOKEN_T> valid_next_tokens;

    // if(this->current_context == _C_EXPR)
    // {
    //     valid_next_tokens = {_TOKEN_PLUS, _TOKEN_MINUS, _TOKEN_MUL, _TOKEN_DIV, _TOKEN_MOD, _TOKEN_SEMI_COL};
    //     if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);
    // }

    // else if(this->current_context == _C_OUTPUT)
    // {
    //     valid_next_tokens = {_TOKEN_PLUS, _TOKEN_MINUS, _TOKEN_MUL, _TOKEN_DIV, _TOKEN_MOD, _TOKEN_SEMI_COL, _TOKEN_VAR, _TOKEN_STRING, _TOKEN_NEW_LINE};
    //     if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);
    // }


    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL || this->current_token._TOKEN_TYPE == _TOKEN_COLON){
        _int.add_child(this->current_token);
        return _int;
    }

    return _int;
}

Tree Parser::parseBee(){
    Tree bee(makeToken(_TOKEN_BEERUS, BEERUS, "beerus", 0, 0));

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_SEMI_COL){
        bee.add_child(this->current_token);
        return bee;
    }

    return bee;
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

    // std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_STRING, _TOKEN_INT, _TOKEN_VAR, _TOKEN_NEW_LINE, _TOKEN_BEERUS, _TOKEN_MEOWTH, _TOKEN_PIKA};

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
        show.add_child(parseShowVar());
    }

    else if(this->current_token._TOKEN_TYPE == _TOKEN_NEW_LINE)
    {
        show.add_child(parseNewLine());
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
    Tree _if(this->current_token);

    // std::vector<TOKEN_T> valid_next_tokens;

    // if(this->current_context == _C_IF_STMT)
    // {
    //     valid_next_tokens = {_TOKEN_INT, _TOKEN_STRING, _TOKEN_VAR};
    // }

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

    advance();
    // get op
    // get left exper
    // get right exper
    std::vector<Token> left_expr;

    while(1)
    {
        if(this->current_token._TOKEN_TYPE == _TOKEN_EQUALSTO ||
        this->current_token._TOKEN_TYPE == _TOKEN_NOTEQUALS ||
        this->current_token._TOKEN_TYPE == _TOKEN_LESSTHAN ||
        this->current_token._TOKEN_TYPE == _TOKEN_GREATERTHAN ||
        this->current_token._TOKEN_TYPE == _TOKEN_LESSEQU ||
        this->current_token._TOKEN_TYPE == _TOKEN_GREATEREQU) break;

        left_expr.push_back(this->current_token);
        advance();
    }

    Tree cmp_op(this->current_token);

    advance();

    // parse the right expr
    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        cmp_op.add_child(parseStr());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT ||
        this->current_token._TOKEN_TYPE == _TOKEN_VAR)
    {
        cmp_op.add_child(parseAddSub());
    }

    this->counter = 0;
    this->progToken = left_expr;
    advance();

    // parse the left expr
    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        cmp_op.add_child(parseStr());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT ||
        this->current_token._TOKEN_TYPE == _TOKEN_VAR)
    {
        cmp_op.add_child(parseAddSub());
    }

    _if.add_child(cmp_op);
    
    return _if;
}

Tree Parser::parseElse(){
    Tree _else(this->current_token);
    
    // std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_SEMI_COL};

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

    advance();

    if(this->current_token._TOKEN_TYPE == _TOKEN_COLON)
    {
        _else.add_child(Tree(this->current_token));
    }

    return _else;
}

Tree Parser::parseWhile(){
    Tree _while(this->current_token);

    // std::vector<TOKEN_T> valid_next_tokens;

    // if(this->current_context == _C_LOOP_STMT)
    // {
    //     valid_next_tokens = {_TOKEN_INT, _TOKEN_STRING, _TOKEN_VAR};
    // }

    // if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

    advance();
    std::vector<Token> left_expr;

    while(1)
    {
        if(this->current_token._TOKEN_TYPE == _TOKEN_EQUALSTO ||
        this->current_token._TOKEN_TYPE == _TOKEN_NOTEQUALS ||
        this->current_token._TOKEN_TYPE == _TOKEN_LESSTHAN ||
        this->current_token._TOKEN_TYPE == _TOKEN_GREATERTHAN ||
        this->current_token._TOKEN_TYPE == _TOKEN_LESSEQU ||
        this->current_token._TOKEN_TYPE == _TOKEN_GREATEREQU) break;

        left_expr.push_back(this->current_token);
        advance();
    }

    Tree cmp_op(this->current_token);

    advance();

    // parse the right expr
    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        cmp_op.add_child(parseStr());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT ||
        this->current_token._TOKEN_TYPE == _TOKEN_VAR)
    {
        cmp_op.add_child(parseAddSub());
    }

    this->counter = 0;
    this->progToken = left_expr;
    advance();

    // parse the left expr
    if(this->current_token._TOKEN_TYPE == _TOKEN_STRING)
    {
        cmp_op.add_child(parseStr());
    }
    else if(this->current_token._TOKEN_TYPE == _TOKEN_INT ||
        this->current_token._TOKEN_TYPE == _TOKEN_VAR)
    {
        cmp_op.add_child(parseAddSub());
    }

    _while.add_child(cmp_op);
    
    return _while;
}

Tree Parser::parse(std::vector<Token> prog_token){
    this->counter = 0;
    Tree main(makeToken(_TOKEN_START, START_NODE, "", 0, 0));
    
    this->progToken = prog_token;
    advance();

        if(this->current_token._TOKEN_TYPE == _TOKEN_SHOW){
            changeContext(_C_OUTPUT);
            main.add_child(parseShow());
            return main;
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_VAR){
            changeContext(_C_ASSIGNMNET);
            main.add_child(parseVar());
            return main;
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_IF || this->current_token._TOKEN_TYPE == _TOKEN_ELIF){
            changeContext(_C_IF_STMT);
            main.add_child(parseIf());
            return main;
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_ELSE){
            changeContext(_C_ELSE_STMT);
            main.add_child(parseElse());
            return main;
        }

        else if(this->current_token._TOKEN_TYPE == _TOKEN_ENDIF ||
            this->current_token._TOKEN_TYPE == _TOKEN_ENDELSE)
            {
                changeContext(_C_END);
                std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_SEMI_COL};

                if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);

                main.add_child(Tree(this->current_token));
                return main;
            }
        else if(this->current_token._TOKEN_TYPE == _TOKEN_ENDWHILE)
        {
            changeContext(_C_END);
            std::vector<TOKEN_T> valid_next_tokens = {_TOKEN_SEMI_COL};
            if(!find(valid_next_tokens, lookAhead()._TOKEN_TYPE)) displayError(_E_SYNTAX_ERROR, this->current_token._TOKEN_LINE, this->current_token._TOKEN_LINE_NUMBER);
            main.add_child(Tree(this->current_token));
            return main;
        }
        else if(this->current_token._TOKEN_TYPE == _TOKEN_WHILE){
            changeContext(_C_LOOP_STMT);
            main.add_child(parseWhile());
            return main;
        }

        else
        {
            displayError(_E_UNKNOW_TOKEN_ERROR, current_token._TOKEN_LINE, current_token._TOKEN_LINE_NUMBER);
        }
        
    this->progToken.clear();

    return main;
}
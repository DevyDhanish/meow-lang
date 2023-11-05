#include <iostream>
#include "../include/vm.hpp"
#include "../include/token.hpp"
#include "../include/map.hpp"
#include "../include/core.hpp"
#include "../include/map.hpp"
#include "../include/error.hpp"
#include <assert.h>
#include <ctype.h>
#include <string>
#include <cmath>
#include <ctype.h>

#ifdef __linux__
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

std::vector<Byte_code> meow_byte_code;
size_t instruction_pointer = 0;
Byte_code current_instruction;

void meow_pause()
{
    #ifdef _WIN32
        Sleep(1);
    #endif

    #ifdef __linux__
        usleep(50000);
    #endif
}

void advance(){
    if(instruction_pointer < meow_byte_code.size()){
        current_instruction = meow_byte_code[instruction_pointer];
        instruction_pointer++;
    }
    else
    {
        current_instruction = makeByteCode(_OP_EXIT,
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)),
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)));
    }
}

void goback(){
    if(instruction_pointer > 0){
        instruction_pointer--;
        current_instruction = meow_byte_code[instruction_pointer];
    }
    else
    {
        current_instruction = makeByteCode(_OP_EXIT,
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)),
        Tree(makeToken(_TOKEN_EMPTY, "", "", 0, 0)));
    }
}

Byte_code makeByteCode(MEOW_BYTE_CODE _mnemonic, Tree _op1, Tree _op2){
    Byte_code newByteCode;
    newByteCode.mnemonic = _mnemonic;
    newByteCode.operand_1 = _op1;
    newByteCode.operand_2 = _op2;
    return newByteCode;
}

void submitByteCode(Byte_code b_c){
    meow_byte_code.push_back(b_c);
}

void showByteCode(){
    std::unordered_map<_MEOW_BYTE_CODE, std::string> byte_code_table = {
        {_OP_OUT, "_OP_OUT"},
        {_OP_LOOP, "_OP_LOOP"},
        {_OP_CMP_EQU, "_OP_CMP_EQU"},
        {_OP_CMP_LESS, "_OP_CMP_LESS"},
        {_OP_CMP_GREATER,"_OP_CMP_GREATER"},
        {_OP_CMP_NOTEQU,"_OP_CMP_NOTEQU"},
        {_OP_SET,"_OP_SET"},
        {_OP_ELSE,"_OP_ELSE"},
        {_OP_CMP_LESSEQU,"_OP_CMP_LESSEQU"},
        {_OP_CMP_GREAEQU,"_OP_CMP_GREAEQU"},
        {_OP_ENDIF,"_OP_ENDIF"},
        {_OP_ENDELSE,"_OP_ENDELSE"},
        {_OP_IN,"_OP_IN"},
        {_OP_EXIT,"_OP_EXIT"},
        {_OP_ENDWHILE,"_OP_ENDWHILE"},
    };
    int count = 1;
    for(Byte_code i : meow_byte_code){
        std::cout << count << " : " << byte_code_table[i.mnemonic] << " " << i.operand_1.data._TOKEN_VALUE << " " << i.operand_2.data._TOKEN_VALUE << "\n";
        count++;
    }
}

long long solveExpression(Tree root){
    Tree child_tok = root;
    
    if(child_tok.data._TOKEN_TYPE == _TOKEN_PLUS){
        return solveExpression(root.get_child(0)) + solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MUL){
        return solveExpression(root.get_child(0)) * solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MINUS){
        return solveExpression(root.get_child(0)) - solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_DIV){
        return solveExpression(root.get_child(0)) / solveExpression(root.get_child(1));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_MOD){

        return std::fmod(solveExpression(root.get_child(0)), solveExpression(root.get_child(1)));
    }
    else if(child_tok.data._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token var = get(root.data);
        if(var._TOKEN_TYPE != _TOKEN_EMPTY){
            if(var._TOKEN_TYPE == _TOKEN_INT) return std::stoll(var._TOKEN_VALUE);
            else
            {
                displayError(_E_TYPE_ERROR, root.data._TOKEN_LINE, root.data._TOKEN_LINE_NUMBER);
            }
        }
        else
        {
            displayError(_E_UNDECLARED_VAR_ERROR, root.data._TOKEN_LINE, root.data._TOKEN_LINE_NUMBER);
        };
    }
    else
    {
        return std::stoll(child_tok.data._TOKEN_VALUE);
    }

    return 0;
}

Token makeTokenFromValue(TOKEN_T Token_type, long double val)
{
    return makeToken(Token_type, std::to_string(val), "", 0, 0);
}

bool isOperator(Token op)
{
    if(
        op._TOKEN_TYPE == _TOKEN_PLUS ||
        op._TOKEN_TYPE == _TOKEN_MINUS ||
        op._TOKEN_TYPE == _TOKEN_MUL ||
        op._TOKEN_TYPE == _TOKEN_DIV ||
        op._TOKEN_TYPE == _TOKEN_MOD
        )
    {
        return true;
    }

    return false;
}

bool compareEquals(Token left_op, Token right_op, Token ori_left, Token ori_right)
{
    if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    {
        return(format_string(left_op._TOKEN_VALUE) == format_string(right_op._TOKEN_VALUE));
    }
    else if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        displayError(_E_CMP_ERROR, ori_left._TOKEN_LINE, ori_left._TOKEN_LINE_NUMBER);
        return 0;
    }
    else
    {
        return(std::stoll(left_op._TOKEN_VALUE) == std::stoll(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareNotEquals(Token left_op, Token right_op, Token ori_left, Token ori_right)
{
    if(left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING)
    {
        return(format_string(left_op._TOKEN_VALUE) != format_string(right_op._TOKEN_VALUE));
    }
    else if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        displayError(_E_CMP_ERROR, ori_left._TOKEN_LINE, ori_left._TOKEN_LINE_NUMBER);
        return 0;
    }
    else
    {
        return(std::stoll(left_op._TOKEN_VALUE) != std::stoll(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareLessEquals(Token left_op, Token right_op, Token ori_left, Token ori_right)
{
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING) ||
        (left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        displayError(_E_CMP_ERROR, ori_left._TOKEN_LINE, ori_left._TOKEN_LINE_NUMBER);
        return 0;
    }
    else
    {
        return(std::stoll(left_op._TOKEN_VALUE) <= std::stoll(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareGreaterEquals(Token left_op, Token right_op, Token ori_left, Token ori_right)
{
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING) ||
        (left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        displayError(_E_CMP_ERROR, ori_left._TOKEN_LINE, ori_left._TOKEN_LINE_NUMBER);
        return 0;
    }
    else
    {
        return(std::stoll(left_op._TOKEN_VALUE) >= std::stoll(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareLess(Token left_op, Token right_op, Token ori_left, Token ori_right)
{
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING) ||
        (left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        displayError(_E_CMP_ERROR, ori_left._TOKEN_LINE, ori_left._TOKEN_LINE_NUMBER);
        return 0;
    }
    else
    {
        return(std::stoll(left_op._TOKEN_VALUE) < std::stoll(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareGreater(Token left_op, Token right_op, Token ori_left, Token ori_right)
{
    if((left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_INT) ||
        (left_op._TOKEN_TYPE == _TOKEN_INT && right_op._TOKEN_TYPE == _TOKEN_STRING) ||
        (left_op._TOKEN_TYPE == _TOKEN_STRING && right_op._TOKEN_TYPE == _TOKEN_STRING))
    {
        displayError(_E_CMP_ERROR, ori_left._TOKEN_LINE, ori_left._TOKEN_LINE_NUMBER);
        return 0;
    }
    else
    {
        return(std::stoll(left_op._TOKEN_VALUE) > std::stoll(right_op._TOKEN_VALUE));
    }

    return false;
}

bool compareTokens(MEOW_BYTE_CODE cmp_type, Tree left_op, Tree right_op){

    typedef bool (*compareFunctionPtr)(Token, Token, Token, Token);

    compareFunctionPtr cmpfncptr;

    switch(cmp_type){
        case _OP_CMP_EQU:
            cmpfncptr = &compareEquals;
            break;
        case _OP_CMP_NOTEQU:
            cmpfncptr = &compareNotEquals;
            break;
        case _OP_CMP_LESSEQU:
            cmpfncptr = &compareLessEquals;
            break;
        case _OP_CMP_GREAEQU:
            cmpfncptr = &compareGreaterEquals;
            break;
        case _OP_CMP_LESS:
            cmpfncptr = &compareLess;
            break;
        case _OP_CMP_GREATER:
            cmpfncptr = &compareGreater;
            break;
        default:
            cmpfncptr = &compareEquals;
    }

    if((left_op.data._TOKEN_TYPE == _TOKEN_VAR && right_op.data._TOKEN_TYPE == _TOKEN_VAR))
    {
        Token l_var = get(left_op.data);
        Token r_var = get(right_op.data);

        if(l_var._TOKEN_TYPE == _TOKEN_EMPTY) displayError(_E_UNDECLARED_VAR_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);

        if(r_var._TOKEN_TYPE == _TOKEN_EMPTY) displayError(_E_UNDECLARED_VAR_ERROR, right_op.data._TOKEN_LINE, right_op.data._TOKEN_LINE_NUMBER);

        return (*cmpfncptr)(l_var, r_var, left_op.data, right_op.data);
    }

    // string
    else if(left_op.data._TOKEN_TYPE == _TOKEN_VAR && right_op.data._TOKEN_TYPE == _TOKEN_STRING)
    {
        Token l_var = get(left_op.data);

        if(l_var._TOKEN_TYPE == _TOKEN_EMPTY) displayError(_E_UNDECLARED_VAR_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);

        return (*cmpfncptr)(l_var, right_op.data, left_op.data, right_op.data);
    }

    else if(left_op.data._TOKEN_TYPE == _TOKEN_STRING && right_op.data._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token r_var = get(right_op.data);

        if(r_var._TOKEN_TYPE == _TOKEN_EMPTY) displayError(_E_UNDECLARED_VAR_ERROR, right_op.data._TOKEN_LINE, right_op.data._TOKEN_LINE_NUMBER);

        return (*cmpfncptr)(left_op.data, r_var, left_op.data, right_op.data);
    }

    else if(left_op.data._TOKEN_TYPE == _TOKEN_INT && right_op.data._TOKEN_TYPE == _TOKEN_STRING)
    {
        displayError(_E_CMP_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);
    }

    else if(left_op.data._TOKEN_TYPE == _TOKEN_STRING && right_op.data._TOKEN_TYPE == _TOKEN_INT)
    {
        displayError(_E_CMP_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);
    }

    else if(isOperator(left_op.data) && right_op.data._TOKEN_TYPE == _TOKEN_STRING)
    {
        displayError(_E_CMP_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);
    }

    else if(left_op.data._TOKEN_TYPE == _TOKEN_STRING && isOperator(right_op.data))
    {
        displayError(_E_CMP_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);
    }

    // operator
    else if((isOperator(left_op.data) && isOperator(right_op.data)) ||
            (isOperator(left_op.data) && right_op.data._TOKEN_TYPE == _TOKEN_INT) ||
            (left_op.data._TOKEN_TYPE == _TOKEN_INT && isOperator(right_op.data)) ||
            (left_op.data._TOKEN_TYPE == _TOKEN_INT && right_op.data._TOKEN_TYPE == _TOKEN_INT))
    {
        Token left_val = makeTokenFromValue(_TOKEN_INT, solveExpression(left_op));
        Token right_val = makeTokenFromValue(_TOKEN_INT, solveExpression(right_op));
        return (*cmpfncptr)(left_val, right_val, left_op.data, right_op.data);
    }

    // variables
    else if(left_op.data._TOKEN_TYPE == _TOKEN_VAR && (right_op.data._TOKEN_TYPE == _TOKEN_INT || isOperator(right_op.data)))
    {
        Token l_var = get(left_op.data);
        if(l_var._TOKEN_TYPE == _TOKEN_EMPTY) displayError(_E_UNDECLARED_VAR_ERROR, left_op.data._TOKEN_LINE, left_op.data._TOKEN_LINE_NUMBER);
        Token right_val = makeTokenFromValue(_TOKEN_INT, solveExpression(right_op));
        return (*cmpfncptr)(l_var, right_val, left_op.data, right_op.data);
    }

    else if((left_op.data._TOKEN_TYPE == _TOKEN_INT || isOperator(left_op.data)) && right_op.data._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token r_var = get(right_op.data);
        if(r_var._TOKEN_TYPE == _TOKEN_EMPTY) displayError(_E_UNDECLARED_VAR_ERROR, right_op.data._TOKEN_LINE, right_op.data._TOKEN_LINE_NUMBER);
        Token left_val = makeTokenFromValue(_TOKEN_INT, solveExpression(left_op));
        return (*cmpfncptr)(left_val, r_var, left_op.data, right_op.data);
    }

    else
    {
        return (*cmpfncptr)(left_op.data, right_op.data, left_op.data, right_op.data);
    }
}

void runIfBlock()
{
    int curr_if_indent = current_instruction.operand_1.data._INDENTATION;
    advance();
    while (1)
    {

        if(current_instruction.mnemonic == _OP_ENDIF && 
        current_instruction.operand_1.data._INDENTATION == curr_if_indent) break;

        else if((current_instruction.operand_1.data._INDENTATION == curr_if_indent && current_instruction.mnemonic != _OP_ENDIF) || current_instruction.mnemonic == _OP_EXIT)
        {
            displayError(_E_SYNTAX_ERROR, "if was not ended with `fi;` or Incorrect Indent was used", current_instruction.operand_1.data._TOKEN_LINE_NUMBER);
        }

        runByteCode();
        advance();
    }

    advance();

    if(current_instruction.mnemonic == _OP_ELSE)
    {
        //int curr_else_indent = current_instruction.operand_1._INDENTATION;
        advance();
        while(1)
        {

            if(current_instruction.mnemonic == _OP_ENDELSE && 
            current_instruction.operand_1.data._INDENTATION == curr_if_indent) break;

            else if((current_instruction.operand_1.data._INDENTATION == curr_if_indent && current_instruction.mnemonic != _OP_ENDELSE) || current_instruction.mnemonic == _OP_EXIT)
            {
                displayError(_E_SYNTAX_ERROR, "else was not ended with `el;` or Incorrect Indent was used", current_instruction.operand_1.data._TOKEN_LINE_NUMBER);
            }

            advance();
        };
        
    }
    else
    {
        goback();
    }
}

void runElseBlock()
{
    int curr_if_indent = current_instruction.operand_1.data._INDENTATION;
    advance();
    while(1)
    {
        if(current_instruction.mnemonic == _OP_ENDIF && 
        current_instruction.operand_1.data._INDENTATION == curr_if_indent) break;
        else if((current_instruction.operand_1.data._INDENTATION == curr_if_indent && current_instruction.mnemonic != _OP_ENDIF) || current_instruction.mnemonic == _OP_EXIT)
        {
            displayError(_E_SYNTAX_ERROR, "if was not ended with `if;` or Incorrect Indent was used", current_instruction.operand_1.data._TOKEN_LINE_NUMBER);
        }
        
        advance();
    }

    advance();

    if(current_instruction.mnemonic == _OP_ELSE)
    {
        int curr_else_indent = current_instruction.operand_1.data._INDENTATION;
        advance();

        while(1)
        {
            if(current_instruction.mnemonic == _OP_ENDELSE && 
            current_instruction.operand_1.data._INDENTATION == curr_else_indent) break;
            else if((current_instruction.operand_1.data._INDENTATION == curr_else_indent && current_instruction.mnemonic != _OP_ENDELSE) || current_instruction.mnemonic == _OP_EXIT)
            {
                displayError(_E_SYNTAX_ERROR, "else was not ended with `el;` or Incorrect Indent was used", current_instruction.operand_1.data._TOKEN_LINE_NUMBER);
            }

            runByteCode();
            advance();
        }
    }

    else
    {
        goback();
    }
}

void runLoopBlock()
{
    int while_indent = current_instruction.operand_1.data._INDENTATION;
    size_t while_instruction = instruction_pointer;
    advance();
    bool flag = compareTokens(current_instruction.mnemonic, current_instruction.operand_1, current_instruction.operand_2);
    while(flag)
    {
        advance();

        while(1)
        {
            if(current_instruction.mnemonic == _OP_ENDWHILE && 
            current_instruction.operand_1.data._INDENTATION == while_indent){
                instruction_pointer = while_instruction;
                advance();
                break;
            }
            else if((current_instruction.operand_1.data._INDENTATION == while_indent && current_instruction.mnemonic != _OP_ENDWHILE) || current_instruction.mnemonic == _OP_EXIT)
            {
                displayError(_E_SYNTAX_ERROR, "while was not ended with `end;` or Incorrect Indent was used", current_instruction.operand_1.data._TOKEN_LINE_NUMBER);
            }

            runByteCode();
            advance();
        }

        flag = compareTokens(current_instruction.mnemonic, current_instruction.operand_1, current_instruction.operand_2);
    }

    advance();
    while(1)
    {
        if(current_instruction.mnemonic == _OP_ENDWHILE && 
        current_instruction.operand_1.data._INDENTATION == while_indent){
            break;
        }
        else if((current_instruction.operand_1.data._INDENTATION == while_indent && current_instruction.mnemonic != _OP_ENDWHILE) || current_instruction.mnemonic == _OP_EXIT)
        {
            displayError(_E_SYNTAX_ERROR, "while was not ended with `end;` or Incorrect Indent was used", current_instruction.operand_1.data._TOKEN_LINE_NUMBER);
        }
        
        advance();
    }
}

void output(Tree root)
{
    if(root.data._TOKEN_TYPE == _TOKEN_VAR){
        Token var = get(root.data);
        if(var._TOKEN_TYPE == _TOKEN_STRING)
        {
            std::cout << format_string(var._TOKEN_VALUE);
        }
        else if(var._TOKEN_TYPE == _TOKEN_INT)
        {
            std::cout << var._TOKEN_VALUE;
        }
        else
        {
            displayError(_E_UNDECLARED_VAR_ERROR, root.data._TOKEN_LINE, root.data._TOKEN_LINE_NUMBER);
        }
    }
    else if(isOperator(root.data))
    {
        std::cout << solveExpression(root);
    }
    else if(root.data._TOKEN_TYPE == _TOKEN_STRING){
        std::cout << format_string(root.data._TOKEN_VALUE);
    }
    else if(root.data._TOKEN_TYPE == _TOKEN_NEW_LINE)
    {
        std::cout << "\n";
    }
    else if(root.data._TOKEN_TYPE == _TOKEN_PIKA || root.data._TOKEN_TYPE == _TOKEN_AYO || root.data._TOKEN_TYPE == _TOKEN_MEOWTH || root.data._TOKEN_TYPE == _TOKEN_BEERUS)
    {
        std::cout << root.data._TOKEN_VALUE;
    }
    else if(root.data._TOKEN_TYPE == _TOKEN_MASTRUBATE)
    {
        int i = 0;

        while(i < mastrubate_emojies.size())
        {
            std::cout << mastrubate_emojies[i] << "\n";
            meow_pause();
            #ifdef __linux__
            system("clear");
            #endif
            #ifdef _WIN32
            system("cls");
            #endif
            i++;
        }
        std::cout << mastrubate_emojies[mastrubate_emojies.size() - 1] << "\n";
        std::cout << "Oh my......take that on your face.";
        std::cout << "\n";
    }
    else if(root.data._TOKEN_TYPE == _TOKEN_INT)
    {
        std::cout << root.data._TOKEN_VALUE;
    }

    if(root.childs.size() > 0) output(root.get_child(0));
}

void runByteCode(){
    if(current_instruction.mnemonic == _OP_SET){
        if(current_instruction.operand_2.data._TOKEN_TYPE == _TOKEN_INT || 
        isOperator(current_instruction.operand_2.data) || 
        current_instruction.operand_2.data._TOKEN_TYPE == _TOKEN_VAR)
        {
            Token val = makeTokenFromValue(_TOKEN_INT, solveExpression(current_instruction.operand_2));
            insert(current_instruction.operand_1.data, val);
        }

        else
        {
            insert(current_instruction.operand_1.data, current_instruction.operand_2.data);
        }    
    }

    else if(current_instruction.mnemonic == _OP_IN){
        std::string input;
        std::cout << format_string(current_instruction.operand_2.data._TOKEN_VALUE);
        getline(std::cin, input);
        Token val;
        // check if the input is a int or string
        if(isdigit(input[0]))
        {
            val = makeToken(_TOKEN_INT, input, "", current_instruction.operand_1.data._TOKEN_LINE_NUMBER, current_instruction.operand_1.data._INDENTATION);
        }
        else
        {
            val = makeToken(_TOKEN_STRING, input, "", current_instruction.operand_1.data._TOKEN_LINE_NUMBER, current_instruction.operand_1.data._INDENTATION);
        }

        current_instruction.operand_2.data = val;
        insert(current_instruction.operand_1.data, current_instruction.operand_2.data);
    }

    else if(current_instruction.mnemonic == _OP_OUT){
        output(current_instruction.operand_1);
    }

    else if(current_instruction.mnemonic == _OP_CMP_EQU ||
            current_instruction.mnemonic == _OP_CMP_LESS ||
            current_instruction.mnemonic == _OP_CMP_GREATER ||
            current_instruction.mnemonic == _OP_CMP_NOTEQU  ||
            current_instruction.mnemonic == _OP_CMP_LESSEQU  ||
            current_instruction.mnemonic == _OP_CMP_GREAEQU
        )
        {

        if(compareTokens(current_instruction.mnemonic, current_instruction.operand_1, current_instruction.operand_2))
        {
            runIfBlock();
        }
        else
        {
            runElseBlock();
        }
    }

    else if(current_instruction.mnemonic == _OP_LOOP)
    {
        runLoopBlock();
    }
}

void run()
{
    advance();
    while(current_instruction.mnemonic != _OP_EXIT)
    {
        runByteCode();

        advance();
    }
}
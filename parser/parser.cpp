#include "../include/internals/mewcore_ast.hpp"
#include "../include/internals/mewdefs.hpp"
#include "../include/token.hpp"
#include "parser.hpp"
#include <stdlib.h>
#include <string.h>
#include <iostream>

bool comsume_token(Parser &p, TOKEN_T type)
{
    if(p.tokens[p.counter]._TOKEN_TYPE == type)
    {
        p.counter++;
        return true;
    }
    else
    {
        return false;
    }
}

void *genNameAST_fromToken(Parser &p) {
    if (p.tokens[p.counter]._TOKEN_TYPE != _TOKEN_VAR) {
        printf("Expected a var token but got Token of type - %d\n", p.tokens[p.counter]._TOKEN_TYPE);
        return NULL;
    }

    meowConstObj *varName = (meowConstObj *)malloc(sizeof(meowConstObj));
    if (varName == NULL) {
        std::cout << "Failed to allocate memory for variable obj\n";
        return NULL; // Return NULL on allocation failure
    }

    varName->kind = _const_kind::Char;

    const char *var_name = p.tokens[p.counter]._TOKEN_VALUE.c_str();
    //size_t len = strlen(var_name) + 1; // Add 1 for null terminator
    varName->data.Char.val = (char *)var_name;
    printf("%c", varName->data.Char.val);
    p.counter++;
    return varName;
}

meowConstObj *const_rule(Parser &p)
{
    void *a;
    if(
        p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_INT    
    )
    {
        meowConstObj *const_val = (meowConstObj *) malloc(sizeof(meowConstObj));
        const_val->kind = _const_kind::Int;
        const_val->data.Integer.val = stoll(p.tokens[p.counter]._TOKEN_VALUE);
        p.counter++;
        return const_val;
    }
    else
    {
        std::cout << "Failed to parser const\n";
        return NULL;
    }
}

void *expression_rule(Parser &p)
{
    void *a;

    if(a = const_rule(p))
    {
        expr_ty *const_val = (expr_ty *) malloc(sizeof(const_val));
        const_val->kind = _expr_kind::Const;
        const_val->v.Const.value = (meowConstObj *)a;
        return const_val;
    }
    else
    {
        std::cout << "const_rule() returned NULL\n";
        return NULL;
    }
}

expr_ty *assign_stmt(Parser &p)
{
    // get name
    // consume '='
    // parser expression
    void *var_name;
    void *value;
    if(
       (var_name = genNameAST_fromToken(p))
        &&
        comsume_token(p, _TOKEN_EQU) // `=`
        &&
        (value = expression_rule(p))
    )
    {
        // make assignment token
        expr_ty *_var = (expr_ty *) malloc(sizeof(expr_ty));
        _var->kind = _expr_kind::NameExpr;
        
        expr_ty *var_name_expr = (expr_ty *) malloc(sizeof(var_name));
        var_name_expr->kind = _expr_kind::VarName;
        var_name_expr->v.Name.id = (meowConstObj *)var_name;

        _var->v.NameExpr.target = (expr_ty *) var_name_expr;
        _var->v.NameExpr.value = (expr_ty *)value;
        printf("%c", _var->v.NameExpr.target->v.Name.id);
        return _var;
    }
    else
    {
        std::cout << "genNameAST() || cosume_token() || expression_rule() returned NULL\n";
        return NULL;
    }
}

stmt_ty *simple_stmt(Parser &p)
{
    void *a;
    if(a = assign_stmt(p))
    {
        stmt_ty *assstmt = (stmt_ty *) malloc(sizeof(stmt_ty));
        assstmt->kind = _stmt_kind::Assign;
        assstmt->v.Assign.body = (expr_ty *) a;
        return assstmt;
    }
    else
    {
        std::cout << "assign_stmt() returned NULL\n";
        return NULL;
    }
}

void *file_rule(Parser &p)
{
    mod_ty *result;

    void *a;
    if(a = simple_stmt(p))
    {
        result = (mod_ty *) malloc(sizeof(mod_ty));
        result->Kind = _mod_kind::Module;
        result->v.Module.body = (stmt_ty **) malloc(sizeof(a));
        result->v.Module.body[p.level] = ( stmt_ty *) a;
        return result;
    }
    else
    {
        std::cout << "simple_stmt returned NULL\n";
        return NULL;
    }
}

struct Parser gen_parser(const std::vector<Token> &toks, size_t c, size_t l)
{
    struct Parser p;
    p.tokens = toks,
    p.counter = c;
    p.level = l;

    return p;
}

void *parse(const std::vector<Token> &token_list, _rule rule)
{
    struct Parser p = gen_parser(token_list, 0, 0);
    
    void *result;

    if(rule == File_Rule)
    {
        result = file_rule(p);
    }
    else
    {
        std::cout << "FileRule returned NULL\n";
        result = NULL;
    }

    return result;
}

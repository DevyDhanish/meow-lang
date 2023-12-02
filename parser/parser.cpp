#include "../include/internals/mewcore_ast.hpp"
#include "../include/internals/mewdefs.hpp"
#include "../include/token.hpp"
#include "../include/internals/list/list.hpp"
#include "parser.hpp"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <assert.h>

Token empty_token = makeToken(_TOKEN_EMPTY, "", "", 0);

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

bool expect_token(Parser &p, TOKEN_T type)
{
    return (p.tokens[p.counter]._TOKEN_TYPE == type);
}

struct Parser gen_parser(const std::vector<Token> &toks, size_t c, size_t l)
{
    struct Parser p;
    p.tokens = toks,
    p.counter = c;
    p.level = l;

    return p;
}

// creates a meowConstObj with the given type, you have to manually set the data
// a - > int
// b - > float
// c - > char
void *genMeowConstObj(Parser &p, Token a, Token b, Token c, _const_kind type)
{
    meowConstObj *const_obj = (meowConstObj *) malloc(sizeof(meowConstObj));
    if(!const_obj)
    {
        printf("Failed allocate mem for meowConstObj\n");
        return NULL;
    }
    const_obj->kind = type;

    if(type == _const_kind::Char)
    {
        const_obj->data.Char.val = (char *)malloc(c._TOKEN_VALUE.size());
        if(!const_obj->data.Char.val)
        {
            printf("Failed to allocate mem for copying variable name\n");
            return NULL;
        }
        strncpy(const_obj->data.Char.val, c._TOKEN_VALUE.c_str(), c._TOKEN_VALUE.size());
        const_obj->data.Char.val[c._TOKEN_VALUE.size()] = '\0';
    }

    else if(type == _const_kind::Int)
    {
        const_obj->data.Integer.val = stoll(a._TOKEN_VALUE);
    }

    else if( type == _const_kind::Float)
    {
        char *e;
        errno = 0;
        const_obj->data.Float.val = std::strtold(b._TOKEN_VALUE.c_str(), &e);
    }

    p.counter++;
    return const_obj;
}

void *genConst_expr(meowConstObj *a)
{
    expr_ty *const_obj = (expr_ty *) malloc(sizeof(expr_ty));
    if(!const_obj)
    {
        printf("Failed to allocate mem for expr_ty obj\n");
        return NULL;
    }
    const_obj->kind == _expr_kind::Const;
    const_obj->v.Const.value = a;

    return const_obj;
}

void *genName_expr(meowConstObj *a)
{
    expr_ty *Name_expr = (expr_ty *) malloc(sizeof(expr_ty));
    if(!Name_expr)
    {
        printf("Failed to allocate mem for Name_expr\n");
        return NULL;
    }
    Name_expr->kind = _expr_kind::VarName;
    Name_expr->v.Name.id = a;

    return Name_expr;
}

// a -> target
// b -> value
void *genNameexpr_expr(expr_ty *a, expr_ty *b)
{
    expr_ty *variable = (expr_ty *) malloc(sizeof(expr_ty));
    if(!variable)
    {
        printf("Failed to allocate mem for variable expr\n");
        return NULL;
    }
    variable->kind = _expr_kind::NameExpr;
    variable->v.NameExpr.target = a;
    variable->v.NameExpr.value = b;
    
    return variable;
}

void *genAssign_stmt(expr_ty *a)
{
    stmt_ty *assign_stmt = (stmt_ty *) malloc(sizeof(stmt_ty));
    if(!assign_stmt)
    {
        printf("Failed to allocate mem for Assign stmt\n");
        return NULL;
    }
    assign_stmt->kind = _stmt_kind::Assign;
    assign_stmt->v.Assign.body = a;

    return assign_stmt;
}

// void *genModule_mod(Parser &p, stmt_ty *body)
// {
//     mod_ty *result = (mod_ty *) malloc(sizeof(mod_ty));
//     result->Kind = _mod_kind::Module;
//     result->v.Module.body = (stmt_ty **) malloc(sizeof(body));
//     result->v.Module.body[p.level] = ( stmt_ty *) body;
// }

void *const_rule(Parser &p)
{
    void *a;
    if(
        p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_INT    
    )
    {
        meowConstObj *const_val = (meowConstObj *) genMeowConstObj(p, p.tokens[p.counter], empty_token, empty_token, _const_kind::Int);

        p.counter++;
        return const_val;
    }
    if( p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_STRING )
    {
        meowConstObj *const_val = (meowConstObj *) genMeowConstObj(p, empty_token, empty_token, p.tokens[p.counter], _const_kind::Char);
        p.counter++;
        return const_val;
    }
    if ( p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_FLOAT )
    {
        meowConstObj *const_val = (meowConstObj *) genMeowConstObj(p, empty_token, p.tokens[p.counter], empty_token, _const_kind::Float);
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
        expr_ty *const_val = (expr_ty *) genConst_expr((meowConstObj *)a);
        return const_val;
    }
    else
    {
        std::cout << "const_rule() returned NULL\n";
        return NULL;
    }
}

void *assign_stmt(Parser &p)
{
    // get name
    // consume '='
    // parser expression
    void *var_name;
    void *value;
    assert(p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_VAR);
    if(
       (var_name = genMeowConstObj(p, empty_token, empty_token, p.tokens[p.counter], _const_kind::Char)) // store variable name
        &&
        comsume_token(p, _TOKEN_EQU) // `=`
        &&
        (value = expression_rule(p))
    )
    {
        expr_ty *varname_expr = (expr_ty *) genName_expr( (meowConstObj *) var_name);
        expr_ty *variable = (expr_ty *) genNameexpr_expr(varname_expr, (expr_ty *) value);
        return variable;
    }
    else
    {
        std::cout << "genNameAST() || cosume_token() || expression_rule() returned NULL\n";
        return NULL;
    }
}

void *simple_stmt(Parser &p)
{
    void *a;
    if(a = assign_stmt(p))
    {
        stmt_ty *assign_stmt = (stmt_ty *) genAssign_stmt((expr_ty *) a);
        return assign_stmt;
    }
    else
    {
        std::cout << "assign_stmt() returned NULL\n";
        return NULL;
    }
}

void *file_rule(Parser &p)
{
    void *a;
    mod_ty *result = (mod_ty *) malloc(sizeof(mod_ty));
    result->Kind = _mod_kind::Module;
    result->v.Module.body = NULL;

again:
    if(a = simple_stmt(p))
    {
        result->v.Module.body = insert(result->v.Module.body, (stmt_ty *) a);
        p.level++;  // no use tbh
        //p.counter++;
    }
    else
    {
        std::cout << "simple_stmt returned NULL\n";
        return NULL;
    }

    if(p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_EOT) return result;

    goto again;
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

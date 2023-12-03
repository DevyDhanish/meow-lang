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

bool consume_token(Parser &p, TOKEN_T type)
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

void *genModule_mod()
{
    mod_ty *result = (mod_ty *) malloc(sizeof(mod_ty));
    if(!result)
    {
        printf("Failed to allocate mem for mod_ty\n");
        return NULL;
    }
    result->Kind = _mod_kind::Module;
    result->v.Module.body = NULL;

    return result;
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
    const_obj->kind = _expr_kind::Const;
    const_obj->v.Const.value = a;

    switch (const_obj->v.Const.value->kind)
    {
    case _const_kind::Char :
        printf("DEBUG::Created a const of value {%s}\n", a->data.Char.val);
        break;
    case _const_kind::Float :
        printf("DEBUG::Created a const of value {%ld}\n", a->data.Float.val);
        break;
    case _const_kind::Int :
        printf("DEBUG::Created a const of value {%d}\n", a->data.Integer.val);
        break;
    default:
        break;
    }

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

void *genBinop_expr(expr_ty *left, _oper op, expr_ty *right)
{   
    expr_ty *a = (expr_ty *) malloc(sizeof(expr_ty));
    if(!a)
    {
        printf("Failed to allocate mem for bin op\n");
    }
    a->kind = _expr_kind::BinOp;
    a->v.BinOp.left = left;
    a->v.BinOp.op = op;
    a->v.BinOp.right = right;

    switch(left->kind)
    {
        case _expr_kind::BinOp:
            printf("DEBUG::Created a binary operator node - lhs kind : {BinOp}\n");
            break;
        
        case _expr_kind::Const:
            printf("DEBUG::Created a binary operator node - lhs kind : {Const}\n");
            break;
        
        default:
            break;
    }

    switch (right->kind)
    {
        case _expr_kind::BinOp:
            printf("DEBUG::Created a binary operator node - rhs kind : {BinOp}\n");
            break;
        
        case _expr_kind::Const:
            printf("DEBUG::Created a binary operator node - rhs kind : {Const}\n");
            break;
        
        default:
            break;
    }

    return a;
}

void *const_rule(Parser &p)
{
    void *a;
    meowConstObj *const_val;
    if(
        p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_BRAOPEN
    )
    {
        p.counter++;
        a = expression_rule(p);
        if(p.tokens[p.counter]._TOKEN_TYPE != _TOKEN_BRACLOSE)
        {
            printf("Error acpected `)` but got token %d\n", p.tokens[p.counter]);
        }
    }
    else if(
        p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_INT    
    )
    {
        const_val = (meowConstObj *) genMeowConstObj(p, p.tokens[p.counter], empty_token, empty_token, _const_kind::Int);
    }
    else if( p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_STRING )
    {
        const_val = (meowConstObj *) genMeowConstObj(p, empty_token, empty_token, p.tokens[p.counter], _const_kind::Char);
    }
    else if ( p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_FLOAT )
    {
        const_val = (meowConstObj *) genMeowConstObj(p, empty_token, p.tokens[p.counter], empty_token, _const_kind::Float);
    }
    else
    {
        std::cout << "Failed to parser const\n";
        return NULL;
    }

    return const_val;
}

void *expression_rule(Parser &p)
{
    // re write
    //assert(p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_INT);
    void *a = const_rule(p);

    expr_ty *lhs = (expr_ty *) genConst_expr((meowConstObj *) a);

    //assert(p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_PLUS);
    while(
        p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_PLUS
    )
    {
        consume_token(p, _TOKEN_PLUS);  // eat `+`
        expr_ty *rhs;
        rhs = (expr_ty *) genConst_expr ( (meowConstObj *) const_rule (p));

        expr_ty *binop;
        binop = (expr_ty *) genBinop_expr((expr_ty *)lhs, _oper::Add, (expr_ty *) rhs);
        lhs = binop;

    }

    p.counter++;
    return lhs;
}

void *assign_stmt(Parser &p)
{
    // get name
    // consume '='
    // parser expression
    void *var_name;
    void *value;
    //printf("%d\n", p.counter);
    assert(p.tokens[p.counter]._TOKEN_TYPE == _TOKEN_VAR);
    if(
       (var_name = genMeowConstObj(p, empty_token, empty_token, p.tokens[p.counter], _const_kind::Char)) // store variable name
        &&
        consume_token(p, _TOKEN_EQU) // `=`
        &&
        (value = expression_rule(p))
    )
    {
        expr_ty *varname_expr = (expr_ty *) genName_expr( (meowConstObj *) var_name);
        expr_ty *variable = (expr_ty *) genNameexpr_expr(varname_expr, (expr_ty *) value);
        printf("DEBUG::Parsed a variable with name {%s} and kind : {%d}\n", variable->v.NameExpr.target->v.Name.id->data.Char.val, variable->v.NameExpr.value->kind);
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
        printf("DEBUG::Parsed assign_stmt of kind -> %d\n", assign_stmt->v.Assign.body->kind);
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
    mod_ty *result = (mod_ty *) genModule_mod();

again:
    if(a = simple_stmt(p))
    {
        result->v.Module.body = insert(result->v.Module.body, (stmt_ty *) a);
        printf("DEBUG::Parsed simple stmt\n");
        p.level++;  // no use tbh
        printf("DEBUG::Module inserted at level %d\n", p.level);
        //p.counter++;
    }
    else
    {
        std::cout << "simple_stmt returned NULL\n";
        return NULL;
    }

    //return result;

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
        printf("DEBUG::Parsing done Rule used - file_rule()\n");
    }
    else
    {
        std::cout << "FileRule returned NULL\n";
        result = NULL;
    }

    return result;
}

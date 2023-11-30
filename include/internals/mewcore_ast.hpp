#pragma once

#include "mewdefs.hpp"
#include <vector>

typedef struct _mod mod_ty;
typedef struct _stmt stmt_ty;
typedef struct _expr expr_ty;

enum _oper { Add, Sub, Mult, MatMult, Div, Mod, Pow,
                         LShift, RShift, BitOr, BitXor, BitAnd,
                         FloorDiv };

enum _expr_kind { BinOp, NameExpr, Const, VarName };

enum _stmt_kind { FunctionDef, ClassDef,
                  Return, Delete, Assign,
                  For, While, If,
                  Match,
                  Raise, Try, Assert,
                  Import, ImportFrom, Global,
                  Nonlocal, Expr, Pass, Break,
                  Continue };

// a file is a module
enum _mod_kind { Module };

struct _mod
{
    _mod_kind Kind;
    union 
    {
        struct
        {
            _stmt **body;
        } Module;
    } v;
};

struct _stmt
{
    _stmt_kind kind;
    union 
    {
        struct
        {
            expr_ty *body;
        } Assign;
    } v;
};

struct _expr
{
    _expr_kind kind;
    union 
    {
        struct
        {
            expr_ty *left;
            _oper op;
            expr_ty *right;
        } BinOp;

        struct 
        {
            expr_ty *target;
            expr_ty *value;
        } NameExpr;

        struct 
        {
            meowConstObj *value;
        } Const;

        struct
        {
            meowConstObj *id;
        } Name;
    } v;
};
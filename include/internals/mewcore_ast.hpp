#pragma once

#include <vector>
#include "mewcore_obj.hpp"

// base class for stmts, does nothing by default

enum STMT_TYPES { stmt_assign, stmt_show, stmt_if };
enum EXPR_TYPES { expr_const, expr_nameexpr, expr_binary, expr_unary };
enum OP_TYPES { Add, Sub, Mul, Div, Mod, Cmp_equ, Cmp_less, Cmp_lessequ, Cmp_great, Cmp_greatequ, Cmp_notequ, negate };

class Stmts 
{
public:
    virtual int getKind() = 0;
    virtual void printInfo() = 0;
    virtual ~Stmts() = default;
};

class Expr 
{
public:
    virtual int getKind() = 0;
    virtual void printInfo() = 0;
    virtual ~Expr() = default;
};

class UnaryExpr: public Expr
{
public:
    EXPR_TYPES kind;
    OP_TYPES op;
    Expr *value;
    UnaryExpr() {}
    UnaryExpr(Expr *a, OP_TYPES o, EXPR_TYPES k) : value(a), op(o), kind(k) {};

    void printInfo() override
    {
        std::cout << "Kind:"<<kind<<"\n";
    }

    int getKind() override
    {
        return kind;
    }
};

class Const : public Expr
{
public:
    EXPR_TYPES kind;
    MeowObject *value;       // Integer, Float, String etc
    Const() {}  // default constructor
    Const(MeowObject *a, EXPR_TYPES k) : value(a), kind(k) {};

    void printInfo() override
    {
        std::cout << "Kind:"<<kind<<"\n";
    }

    int getKind() override
    {
        return kind;
    }
};

class NameExpr : public Expr
{
public:
    EXPR_TYPES kind;
    Expr *target;        // this will be a const like String
    Expr *value;         // this will be any class inheriting Expr
    NameExpr(){}
    NameExpr(Expr *a, Expr *b, EXPR_TYPES k) : target(a), value(b), kind(k) {};

    void printInfo() override
    {
        std::cout << "Kind:"<<kind<<"\n"; 
    }

    int getKind() override
    {
        return kind;
    }
};

class BinOpExpr : public Expr
{
    public:
    EXPR_TYPES kind;
    Expr *left;
    OP_TYPES op;
    Expr *right;
    BinOpExpr(){}
    BinOpExpr(Expr *a, OP_TYPES o, Expr *b, EXPR_TYPES k) : left(a), op(o), right(b), kind(k) {}

    void printInfo() override
    {
        std::cout << "Kind:" << kind << "\n";
    }

    int getKind() override
    {
        return kind;
    }
};

class AssignmnetStmt : public Stmts
{
public:
    STMT_TYPES kind;
    Expr *value;
    AssignmnetStmt() {}
    AssignmnetStmt(Expr *a, STMT_TYPES k) : value(a), kind(k) {}

    void printInfo() override
    {
        std::cout << "Kind:"<<kind<<"\n"; 
    }

    int getKind() override
    {
        return kind;
    }
};

class ShowStmt : public Stmts
{
public:
    STMT_TYPES kind;
    Expr *value;
    ShowStmt() {}
    ShowStmt(Expr *a, STMT_TYPES k) : value(a), kind (k) {}

    void printInfo() override
    {
        std::cout << "Kind:" << kind << "\n";
    }

    int getKind() override
    {
        return kind;
    }
};

class IfStmt : public Stmts
{
public:
    STMT_TYPES kind;
    Expr *condition;
    std::vector<Stmts *> tbody;
    std::vector<Stmts *> fbody;

    void printInfo() override
    {
        std::cout << "Kind:" << kind << "\n";
    }

    int getKind() override
    {
        return kind;
    }
};

class Module
{
public:
    std::vector<Stmts *> body;

    void addStmt(Stmts *newStmt)
    {
        body.push_back(newStmt);
    }
    void displayStmts();
};
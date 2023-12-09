#pragma once

#include <vector>
#include "mewcore_obj.hpp"

// base class for stmts, does nothing by default
class Stmts 
{
public:
    virtual void *getValue() = 0;
    virtual void printInfo() = 0;
    virtual ~Stmts() = default;
};
class Expr 
{
public:
    virtual void *getValue() = 0;
    virtual void printInfo() = 0;
    virtual ~Expr() = default;
};

class Const : public Expr
{
public:
    std::string kind;
    MeowObject *value;       // Integer, Float, String etc
    Const() {}  // default constructor
    Const(MeowObject *a, std::string k) : value(a) { kind = k; };
    void printInfo() override
    {
        std::cout << "Kind:"<<kind<<"\n";
    }

    void *getValue() override
    {
        return value;
    }
};

class NameExpr : public Expr
{
public:
    std::string kind;
    Expr *target;        // this will be a const like String
    Expr *value;         // this will be any class inheriting Expr
    NameExpr(){}
    NameExpr(Expr *a, Expr *b, std::string k) : target(a), value(b) { kind = k; };
    void printInfo()
    {
        std::cout << "Kind:"<<kind<<"\n"; 
    }
    void *getValue() override
    {
        return value;
    }
};

class AssignmnetStmt : public Stmts
{
public:
    std::string kind;
    Expr *value;
    AssignmnetStmt() {}
    AssignmnetStmt(Expr *a, std::string k) : value(a) { kind = k; }
    void printInfo()
    {
        std::cout << "Kind:"<<kind<<"\n"; 
    }
    void *getValue() override
    {
        return value;
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
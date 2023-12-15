#pragma once
#include <cstdint>
#include <iostream>

enum MEOWOBJECTKIND { IntObj, StringObj, FloatObj, VarObj};

class MeowObject
{
public:
    virtual void printInfo() = 0;
    virtual int getKind() = 0;
    virtual void onShow() = 0;
    virtual void *onAdd(MeowObject *b) = 0;
    virtual void *onSub(MeowObject *b) = 0;
    virtual void *onMul(MeowObject *b) = 0;
    virtual void *onDiv(MeowObject *b) = 0;
    virtual void *onMod(MeowObject *b) = 0;

    virtual void *onCmpE(MeowObject *b) = 0;
    virtual void *onCmpNE(MeowObject *b) = 0;
    virtual void *onCmpL(MeowObject *b) = 0;
    virtual void *onCmpLE(MeowObject *b) = 0;
    virtual void *onCmpG(MeowObject *b) = 0;
    virtual void *onCmpGE(MeowObject *b) = 0;

    virtual void *onNegate() = 0;
    virtual void *onNot() = 0;

    virtual void *onAnd(MeowObject *b) = 0;
    virtual void *onOr(MeowObject *b) = 0;

    virtual ~MeowObject() = default;
};

// These are the data types of Meow lang represented as classes in C++
class Integer : public MeowObject
{
public:
    MEOWOBJECTKIND kind;
    int64_t value;
    Integer() {};
    Integer(int64_t a, MEOWOBJECTKIND k) : value(a), kind(k) { }

    void printInfo() override
    {
        std::cout << "type <Integer>\n";
    }

    int getKind() override
    {
        return kind;
    }


    void onShow() override
    {
        std::cout << value;
    }

    void *onAdd(MeowObject *b) override;
    void *onSub(MeowObject *b) override;
    void *onMod(MeowObject *b) override;
    void *onMul(MeowObject *b) override;
    void *onDiv(MeowObject *b) override;

    void *onCmpE(MeowObject *b) override;
    void *onCmpNE(MeowObject *b) override;
    void *onCmpL(MeowObject *b) override;
    void *onCmpLE(MeowObject *b) override;
    void *onCmpG(MeowObject *b) override;
    void *onCmpGE(MeowObject *b) override;

    void *onNegate() override;
    void *onNot() override;

    void *onAnd(MeowObject *b) override;
    void *onOr(MeowObject *b) override;
};

class String : public MeowObject
{
public:
    std::string value;
    MEOWOBJECTKIND kind;
    String(){}
    String(std::string val, MEOWOBJECTKIND k) : value(val), kind(k) {}

    void printInfo() override
    {
        std::cout << "type <String>\n";
    }
    int getKind() override
    {
        return kind;
    }

    void onShow() override
    {
        std::cout << value;
    }
    void *onAdd(MeowObject *b) override;
    void *onSub(MeowObject *b) override;
    void *onMod(MeowObject *b) override;
    void *onMul(MeowObject *b) override;
    void *onDiv(MeowObject *b) override;

    void *onCmpE(MeowObject *b) override;
    void *onCmpNE(MeowObject *b) override;
    void *onCmpL(MeowObject *b) override;
    void *onCmpLE(MeowObject *b) override;
    void *onCmpG(MeowObject *b) override;
    void *onCmpGE(MeowObject *b) override;

    void *onNegate() override;
    void *onNot() override;

    void *onAnd(MeowObject *b) override;
    void *onOr(MeowObject *b) override;
};

class Float : public MeowObject
{
public:
    long double value;
    MEOWOBJECTKIND kind;
    Float() {}
    Float(long double a, MEOWOBJECTKIND k) : value(a), kind(k) {}

    void printInfo() override
    {
        std::cout << "type <Float>\n";
    }

    int getKind() override
    {
        return kind;
    }

    void onShow() override
    {
        std::cout << value;
    }
    void *onAdd(MeowObject *b) override;
    void *onSub(MeowObject *b) override;
    void *onMod(MeowObject *b) override;
    void *onMul(MeowObject *b) override;
    void *onDiv(MeowObject *b) override;

    void *onCmpE(MeowObject *b) override;
    void *onCmpNE(MeowObject *b) override;
    void *onCmpL(MeowObject *b) override;
    void *onCmpLE(MeowObject *b) override;
    void *onCmpG(MeowObject *b) override;
    void *onCmpGE(MeowObject *b) override;

    void *onNegate() override;
    void *onNot() override;

    void *onAnd(MeowObject *b) override;
    void *onOr(MeowObject *b) override;
};

class Var : public MeowObject
{
public:
    MEOWOBJECTKIND kind;
    std::string value;
    Var() {}
    Var (std::string v, MEOWOBJECTKIND k) : value(v), kind(k) {}

    void printInfo() override
    {
        std::cout << "type <Var>\n";
    }

    int getKind() override
    {
        return kind;
    }

    void onShow() override
    {
        std::cout << "Var type\n";
    }

    void *onAdd(MeowObject *b) override { return NULL; }
    void *onSub(MeowObject *b) override { return NULL; }
    void *onMod(MeowObject *b) override { return NULL; }
    void *onDiv(MeowObject *b) override { return NULL; }
    void *onMul(MeowObject *b) override { return NULL; }

    void *onCmpE(MeowObject *b) override { return NULL; };
    void *onCmpNE(MeowObject *b) override { return NULL; };
    void *onCmpL(MeowObject *b) override { return NULL; };
    void *onCmpLE(MeowObject *b) override { return NULL; };
    void *onCmpG(MeowObject *b) override { return NULL; };
    void *onCmpGE(MeowObject *b) override { return NULL; };

    void *onNegate() override { return NULL; };
    void *onNot() override { return NULL; };

    void *onAnd(MeowObject *b) override { return NULL; };
    void *onOr(MeowObject *b) override { return NULL; };
};
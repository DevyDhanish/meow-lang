#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

enum MEOWOBJECTKIND { Meow_IntObj, Meow_StringObj, Meow_FloatObj, Meow_VarObj, Meow_ArrayObj, Meow_iterObj };

class MeowObject
{
public:
    virtual std::string printInfo() = 0;
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

    virtual bool isIterable() = 0;

    virtual uint32_t getSize() = 0;

    virtual void *getAtIndex(uint64_t idx) = 0;
    virtual void *setAtIndex(uint64_t idx, MeowObject *b) = 0;

    virtual ~MeowObject() = default;
};

// These are the data types of Meow lang represented as classes in C++
class Integer : public MeowObject
{
public:
    MEOWOBJECTKIND kind;
    int64_t value;
    Integer() {};
    Integer(int64_t a, MEOWOBJECTKIND k) : value(a), kind(k) {  }

    std::string printInfo() override
    {
        return "type <Integer>";
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

    void *getAtIndex(uint64_t idx) override;
    void *setAtIndex(uint64_t idx,  MeowObject *b) override;

    bool isIterable() override { return false; } // int can't be iterated so false

    uint32_t getSize() override { return 0; }

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

    std::string printInfo() override
    {
        return "type <String>";
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

    void *getAtIndex(uint64_t idx) override;
    void *setAtIndex(uint64_t idx,  MeowObject *b) override;

    void *onAnd(MeowObject *b) override;
    void *onOr(MeowObject *b) override;

    bool isIterable() override { return true; }

    uint32_t getSize() override { return value.size(); }

};

class Float : public MeowObject
{
public:
    long double value;
    MEOWOBJECTKIND kind;
    Float() {}
    Float(long double a, MEOWOBJECTKIND k) : value(a), kind(k) {}

    std::string printInfo() override
    {
        return "type <Float>";
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

    void *getAtIndex(uint64_t idx) override;
    void *setAtIndex(uint64_t idx,  MeowObject *b) override;

    void *onAnd(MeowObject *b) override;
    void *onOr(MeowObject *b) override;

    bool isIterable() override { return false; }

    uint32_t getSize() override { return 0; }

};

class ArrayObj : public MeowObject
{
public:
    MEOWOBJECTKIND kind;
    std::vector<MeowObject *> values;

    ArrayObj() {}
    ArrayObj(MEOWOBJECTKIND k) : kind(k){}

    void addElements(MeowObject *a)
    {
        values.push_back(a);
    }

    std::string printInfo() override
    {
        return "type <Array>";
    }

    int getKind() override
    {
        return kind;
    }

    void onShow() override
    {
        std::cout << "{";
        int i = 0;
        while (i < values.size())
        {
            ((MeowObject *)values[i])->onShow();
            if((i + 1) != values.size())std::cout << ", ";
            i++;
        }

        std::cout << "}";
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

    void *getAtIndex(uint64_t idx) override;
    void *setAtIndex(uint64_t idx,  MeowObject *b) override;

    void *onAnd(MeowObject *b) override;
    void *onOr(MeowObject *b) override;

    bool isIterable() override { return true; }

    uint32_t getSize() override { return values.size(); }
};

class Var : public MeowObject
{
public:
    MEOWOBJECTKIND kind;
    std::string value;
    Var() {}
    Var (std::string v, MEOWOBJECTKIND k) : value(v), kind(k) {}

    std::string printInfo() override
    {
        return "type <Var>";
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

    void *getAtIndex(uint64_t idx) { return NULL; }
    void *setAtIndex(uint64_t idx,  MeowObject *b) { return NULL; }

    void *onAnd(MeowObject *b) override { return NULL; };
    void *onOr(MeowObject *b) override { return NULL; };

    bool isIterable() override { return false; }

    uint32_t getSize() override { return 0; }
};

class Iter : public MeowObject
{
public:
    MEOWOBJECTKIND kind;
    MeowObject *value;

    Iter(MeowObject *a) : value(a) 
    {
        kind = MEOWOBJECTKIND::Meow_iterObj;
        isExhausted = false;
        iter_couter = 0;
        iterable_size = value->getSize();
    }

    std::string printInfo() override
    {
        return "type <Iter>";
    }

    int getKind() override
    {
        return kind;
    }

    void onShow() override
    {
        std::cout << "Var Iter\n";
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

    void *getAtIndex(uint64_t idx) { return NULL; }
    void *setAtIndex(uint64_t idx,  MeowObject *b) { return NULL; }

    void *onAnd(MeowObject *b) override { return NULL; };
    void *onOr(MeowObject *b) override { return NULL; };

    bool isIterable() override { return false; }

    uint32_t getSize() override { return 0; }

    uint64_t iter_couter;
    bool isExhausted;
    uint64_t iterable_size;

    MeowObject *next()
    {
        MeowObject *val = (MeowObject *)value->getAtIndex(iter_couter);
        iter_couter += 1;

        if(iter_couter >= iterable_size)
        {
            isExhausted = true;
        }

        return val;
    }
};
#pragma once
#include <cstdint>
#include <iostream>

enum MEOWOBJECTKIND { IntObj, StringObj, FloatObj };

class MeowObject
{
public:
    virtual void printInfo() = 0;
    virtual int getKind() = 0;
    virtual ~MeowObject() = default;
};

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
};
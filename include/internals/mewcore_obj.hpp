#pragma once
#include <cstdint>
#include <iostream>

class MeowObject
{
public:
    virtual void printInfo() = 0;
    virtual void *getValue() = 0;
    virtual ~MeowObject() = default;
};

class Integer : public MeowObject
{
public:
    int64_t value;
    Integer() {};
    Integer(int64_t a) { value = a; }

    void printInfo() override
    {
        std::cout << "type <Integer>\n";
    }

    void *getValue() override
    {
        return &value;
    }
};

class String : public MeowObject
{
public:
    std::string value;
    String(){}
    String(std::string val) : value(val) {}

    void printInfo() override
    {
        std::cout << "type <String>\n";
    }
    void *getValue() override
    {
        return &value;
    }
};

class Float : public MeowObject
{
public:
    long double value;
    Float() {}
    Float(long double a) : value(a) {}

    void printInfo() override
    {
        std::cout << "type <Float>\n";
    }
    void *getValue() override
    {
        return &value;
    }
};
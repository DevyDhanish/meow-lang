#include "../../../include/bltins/bltins.hpp"

#include <unordered_map>
#include <iostream>
#include <stack>

void meow_print(std::stack<uint64_t> args)
{
    while (!args.empty())
    {
        ((MeowObject *)args.top())->onShow();
        args.pop();
    }

    std::cout << "\n";
}

std::unordered_map<std::string, BLTIN_METHODS> meow_funcToBltMethodID
{
    {"print", BUILDIN_PRINT},
    {"input", BUILDIN_INPUT},
};

BLTIN_METHODS getBltinMethodId(std::string name)
{
    if(meow_funcToBltMethodID[name])
        return meow_funcToBltMethodID[name];
    else
        return BUILDINT_NULL;
}

void execBltMethod(BLTIN_METHODS id, std::stack<uint64_t> args)
{
    switch (id)
    {
    case BLTIN_METHODS::BUILDIN_PRINT :
        meow_print(args);
        break;
    
    default:
        break;
    }
}

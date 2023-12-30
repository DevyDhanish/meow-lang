#pragma once

#include <unordered_map>
#include <vector>
#include "../internals/mewcore_obj.hpp"
#include <stack>

enum BLTIN_METHODS
{
    BUILDINT_NULL,
    BUILDIN_PRINT,
    BUILDIN_INPUT,
    BUILDIN_LEN,
    BUILDIN_TYPE,
};

extern std::unordered_map<std::string, BLTIN_METHODS> meow_funcToBltMethodID;

BLTIN_METHODS getBltinMethodId(std::string name);

MeowObject *execBltMethod(BLTIN_METHODS id, std::stack<uint64_t> args);
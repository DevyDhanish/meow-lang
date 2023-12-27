#include "../../../include/bltins/bltins.hpp"

#include <unordered_map>
#include <iostream>
#include <stack>
#include <string>
#include "../../../include/lexer.hpp"

MeowObject *meow_print(std::stack<uint64_t> args)
{
    while (!args.empty())
    {
        ((MeowObject *)args.top())->onShow();
        args.pop();
    }

    std::cout << "\n";

    Integer *retVal = new Integer(0, MEOWOBJECTKIND::Meow_IntObj);
    return retVal;
}

MeowObject *meow_len(std::stack<uint64_t> args)
{
    MeowObject *ar = (MeowObject *) args.top();

    if(ar->getKind() == MEOWOBJECTKIND::Meow_ArrayObj)
    {
        Integer *retVal = new Integer(((ArrayObj *)args.top())->values.size(), MEOWOBJECTKIND::Meow_IntObj);
        return retVal;
    }

    std::string val = ((String *) args.top())->value;

    Integer *retVal = new Integer(val.size(), MEOWOBJECTKIND::Meow_IntObj);
    return retVal;
}

MeowObject *meow_input(std::stack<uint64_t> args)
{

    while (!args.empty())
    {
        ((MeowObject *)args.top())->onShow();
        args.pop();
    }

    std::string input_val;

    std::getline(std::cin, input_val);

    if(isFloatS(input_val))
    {
        long double val = std::stold(input_val);
        Float *mewfloat = new Float(val, MEOWOBJECTKIND::Meow_FloatObj);
        return mewfloat;
    }
    else if(isdigitS(input_val))
    {
        long long val;
        val = std::stoll(input_val);
        Integer *retVal = new Integer(val, MEOWOBJECTKIND::Meow_IntObj);
        return retVal;
    }
    else
    {
        String *retVal = new String(input_val, MEOWOBJECTKIND::Meow_StringObj);
        return retVal;
    }

    return NULL;
}

MeowObject *meow_type(std::stack<uint64_t> args)
{
    String *retVal = new String(((MeowObject *)args.top())->printInfo(), MEOWOBJECTKIND::Meow_StringObj);

    return retVal;
}

std::unordered_map<std::string, BLTIN_METHODS> meow_funcToBltMethodID
{
    {"print", BUILDIN_PRINT},
    {"input", BUILDIN_INPUT},
    {"len", BUILDIN_LEN},
    {"type", BUILDIN_TYPE},
};

BLTIN_METHODS getBltinMethodId(std::string name)
{
    if(meow_funcToBltMethodID[name])
        return meow_funcToBltMethodID[name];
    else
        return BUILDINT_NULL;
}

MeowObject *execBltMethod(BLTIN_METHODS id, std::stack<uint64_t> args)
{
    switch (id)
    {

    case BLTIN_METHODS::BUILDIN_PRINT :
        return meow_print(args);
        break;

    case BLTIN_METHODS::BUILDIN_LEN:
        return meow_len(args);
        break;

    case BLTIN_METHODS::BUILDIN_INPUT:
        return meow_input(args);
        break;

    case BLTIN_METHODS::BUILDIN_TYPE:
        return meow_type(args);
        break;

    default:
        break;
    }

    return NULL;
}

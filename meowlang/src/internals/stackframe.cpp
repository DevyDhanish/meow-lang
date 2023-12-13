#include "../../../include/internals/mewcore_stackframe.hpp"


void MEOW_STACKFRAME::pushToStack(uint64_t val)
{
    if(!val)
    {
        return;
    }

    stack_pointer++;

    stack.push_back(val);
}

uint64_t MEOW_STACKFRAME::popFromStack()
{
    if(stack.size() == 0)
    {
        return 0;
    }

    int64_t toPop = stack.back();
    stack_pointer--;
    stack.pop_back();
    return toPop;
}

void MEOW_STACKFRAME::replaceValInStack(uint16_t idx, uint64_t val)
{
    stack[idx] = val;
}

uint64_t MEOW_STACKFRAME::getValFromStack(uint16_t idx)
{
    return stack[idx];
}
#include "../../../include/internals/mewcore_stackframe.hpp"
#include "../../../include/internals/mewcore_ast.hpp"

#include <vector>

std::vector<int64_t *> stack;
std::vector<CONST_POOL *> const_pool;

int stack_pointer = 0;

void MEOW_STACKFRAME::push_stack(int64_t* val)
{
    stack.push_back(val); 
    ++stack_pointer;
}

int64_t *MEOW_STACKFRAME::pop_stack()
{
    --stack_pointer;
    int64_t *val = stack.back();
    stack.pop_back();
    return val;
}

void MEOW_STACKFRAME::store_const(MeowObject *k, MeowObject *v)
{
    MeowObject *varname = ((Const *)k)->value;

    std::cout << "Stored variable id : " << ((String *)varname)->value << "\t" << "value : " << ((Integer *)v)->value << "\n";

    CONST_POOL *cp = new CONST_POOL(k,v);
    const_pool.push_back(cp);
}

MeowObject *MEOW_STACKFRAME::get_const(MeowObject *k)
{
    if(const_pool.size() == 0)
    {
        std::cout << "Invalid operation done on const pool\n";
    }

    for(CONST_POOL *p : const_pool)
    {
        if(((String *)p->key)->value == ((String *)k)->value)
        {
            return p->value;
        }
    }

    return nullptr;
}
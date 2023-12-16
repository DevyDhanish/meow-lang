#include "../../../include/internals/mewcore_constpool.hpp"

struct CONST_PAIR *makeConstPair(MeowObject *k, MeowObject *v)
{
    struct CONST_PAIR *pair = new CONST_PAIR;
    pair->key = k;
    pair->value = v;

    return pair;
}

void put_const(std::vector<const_pair *> &pool, MeowObject *k, MeowObject *v)
{
    if(!v && !k)
    {
        return;
    }

    MeowObject *ifexist = get_const(pool, k);

    if(ifexist)
    {
        for(struct CONST_PAIR *p : pool)
        {   
            if(((Var *)p->key)->value == ((Var *)k)->value)
            {
                p->value = v;   
            }
        }
    }

    pool.push_back(makeConstPair(k, v));
}

MeowObject *get_const(std::vector<const_pair *> &pool, MeowObject *k)
{
    if(!k)
    {
        return NULL;
    }

    //std::cout << "******CONST POOL*******\n";
    for(struct CONST_PAIR *p : pool)
    {
       // std::cout << "Key -> " << ((Var *)k)->value << "\t";
        //std::cout << "Var -> " << ((Var *)p->key)->value << " Value -> ";
        //((MeowObject *)p->value)->onShow();
        //std::cout << "\n";

        if(((Var *)p->key)->value == ((Var *)k)->value)
        {
            //std::cout << "FOUND\n";
            return p->value;
        }
    }

    return NULL;
}
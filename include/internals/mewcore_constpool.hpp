#pragma once

#include "mewcore_obj.hpp"
#include <vector>

struct CONST_PAIR
{
    MeowObject *key;
    MeowObject *value;
};

typedef struct CONST_PAIR const_pair;

const_pair *makeConstPair(MeowObject *k, MeowObject *v);
MeowObject *get_const(std::vector<const_pair *> *pool,  MeowObject *k);
void put_const(std::vector<const_pair *> *pool, MeowObject *k, MeowObject *v);
#pragma once

#include "mewcore_obj.hpp"

class CONST_POOL
{
public:
    MeowObject *key;
    MeowObject *value;

    CONST_POOL(){}
    CONST_POOL(MeowObject *a, MeowObject *b) : key(a), value(b) {}
};
#pragma once

#include <cstdint>
#include <vector>
#include "mewcore_constpool.hpp"

class MEOW_STACKFRAME
{
public:
    //uint32_t stack_pointer;

    //std::vector<CONST_POOL *> const_pool;
    //int64_t **stack;

    void push_stack(int64_t* val);
    int64_t *pop_stack();

    void store_const(MeowObject *k, MeowObject *v);
    MeowObject *get_const(MeowObject *k);

MEOW_STACKFRAME() {
    //stack_pointer = 0;
    //stack = (int64_t **)malloc(256 * sizeof(int64_t *)); // Allocate memory for an array of pointers
    // Check if allocation succeeded or consider using 'new' for C++ allocation
}
};
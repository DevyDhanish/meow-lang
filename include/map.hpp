#pragma once

#include "token.hpp"
#include <vector>

extern std::vector<struct node> map;

typedef struct node{
    Token key;
    Token value;
} node;

void insert(Token key, Token value);
Token get(Token key);
void show();
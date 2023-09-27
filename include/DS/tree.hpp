#pragma once

#include "../token/token.hpp"
#include <vector>
#include <string>

class Tree{
public:
    Token data;
    Tree *parent;
    std::vector<Tree> childs;

    Tree(){};

    Tree(Token value){
        this->data = value;
        this->parent = nullptr;
    }

    void _rt_None_add_child(Tree child);

    Tree _rt_Tree_get_child(size_t index);

    void _rt_None_print_tree();
};
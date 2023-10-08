#pragma once

#include "token.hpp"
#include <vector>
#include <string>

// Class defination for a single tree node
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

    // @brief adds the given argument to this nodes childrens vector
    void add_child(Tree child);

    // @brief returns the children of this ndoe at the given index
    Tree get_child(size_t index);

    // @brief prints the tree using DFS ( DEPTH FRIST SEARCH )
    void print_tree();
};
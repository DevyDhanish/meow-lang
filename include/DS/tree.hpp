#pragma once

#include <vector>
#include <string>
#include <any>

class Tree{
public:
    std::any data;
    Tree *parent;
    std::vector<Tree> childs;

    Tree(){
        this->data = nullptr;
        this->parent = nullptr;
    }

    Tree(std::string value){
        this->data = value;
        this->parent = nullptr;
    }

    Tree(int value){
        this->data = value;
        this->parent = nullptr;
    }

    void _rt_None_add_child(Tree child);

    Tree _rt_Tree_get_child(size_t index);

    void _rt_None_print_tree();
};
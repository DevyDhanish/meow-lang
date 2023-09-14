#include "../../include/DS/tree.hpp"

#include <iostream>
#include <any>

void Tree::_rt_None_add_child(Tree child){
    child.parent = this;
    this->childs.push_back(child);
}

Tree Tree::_rt_Tree_get_child(size_t index){
    return this->childs[index];
}

void Tree::_rt_None_print_tree(){

    if(this->data.type() == typeid(int)){
        std::cout << std::any_cast<int>(this->data) << ",";
    }
    else if(this->data.type() == typeid(std::string)){
        std::cout << std::any_cast<std::string>(this->data ) << ",";
    }


    for(size_t i = 0; i < this->childs.size(); i++){
        this->childs[i]._rt_None_print_tree();
    }
}
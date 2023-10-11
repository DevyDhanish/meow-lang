#include "../include/tree.hpp"

#include <iostream>

// @brief adds the given argument to this nodes childrens vector
void Tree::add_child(Tree child){
    child.parent = this;
    this->childs.push_back(child);
}

// @brief returns the children of this ndoe at the given index
Tree Tree::get_child(size_t index){
    return this->childs[index];
}

// @brief prints the tree using DFS ( DEPTH FRIST SEARCH )
void Tree::print_tree(int level) {
    // Print indentation based on the level
    for (int i = 0; i < level; i++) {
        std::cout << "  "; // You can use spaces or tabs as per your preference
    }

    std::cout << this->data._TOKEN_VALUE << "\n";

    for (size_t i = 0; i < this->childs.size(); i++) {
        this->childs[i].print_tree(level + 1); // Recursively print child trees with increased level
    }
}
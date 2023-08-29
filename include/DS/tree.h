#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef struct tree{
    void *data;
    struct tree **child_nodes;
    size_t child_size;
} tree;

void display(tree *root);

tree *attach(tree *, void *);

#endif
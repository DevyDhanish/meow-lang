#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef struct tree{
    void *data;
    struct tree **childs;
    size_t child_size;
} tree;

void displayTree(tree *root, int c);

tree *attach(tree *, void *);

void freeTree(tree *);

#endif
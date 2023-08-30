#include "../../include/DS/tree.h"
#include <stdio.h>
#include <stdlib.h>

void displayTree(tree *root, int c) {
    if (root == NULL) {
        printf("Root is empty.\n");
        return;
    }

    for (int j = 0; j < c; j++) {
        printf("|__");
    }

    if (c > 0) {
        printf(":- ");
    }

    printf("%s\n", (char *)root->data);

    for (size_t i = 0; i < root->child_size; i++) {
        displayTree(root->childs[i], c + 1);
    }
}

tree *attach(tree *node, void *value){
    tree *newNode = (tree *)malloc(sizeof(tree));
    newNode->data = value;
    newNode->child_size = 0;
    newNode->childs = NULL;

    if(node == NULL){
       node = newNode;
       return node;
    }

    node->childs = (tree **) realloc(node->childs, node->child_size * sizeof(tree));
    node->childs[node->child_size] = newNode;
    node->child_size++;
    
    return node;
}

void freeTree(tree *root){
    for(int i = 0; i < root->child_size; i ++){
        freeTree(root->childs[i]);
    }
    free(root);
}

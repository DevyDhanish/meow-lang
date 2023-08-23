#ifndef LL_H
#define LL_H

#include "../token/token.h"

typedef struct Node {
    token *tok_data;
    struct Node *tok_next;
} Node ;


// @brief displays the linked list
// @param *head - the head of the linked list
void display(Node *temp);


// @brief attatchs the given thing to the end of the linked list
// @param *head - the head of the linked list on which the thing should attatch
// @param *token - the thing to attach
Node *append(Node *head, token *toattatch);


// @brief removes a token from given position
// @param *head - the head of the linked list on which we perform the remove
// @param int position - the position of the node to remove
// TODO implement this function in ll.c
//token *removeT(token *head, int position);

#endif
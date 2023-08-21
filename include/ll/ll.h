#ifndef LL_H
#define LL_H

#include "../token/token.h"


// @brief displays the linked list
// @param *head - the head of the linked list
void display(token *head);


// @brief attatchs the given thing to the end of the linked list
// @param *head - the head of the linked list on which the thing should attatch
// @param *token - the thing to attach
token *append(token *head, token *toattatch);


// @brief removes a token from given position
// @param *head - the head of the linked list on which we perform the remove
// @param int position - the position of the node to remove
token *removeT(token *head, int position);

#endif
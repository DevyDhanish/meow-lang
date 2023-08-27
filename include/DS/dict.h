#ifndef DICT_H
#define DICT_H

#include "list.h"
#include <stdio.h>

typedef struct dict{
    void *key;
    void *value;
} dict;

/*
dict is just a struct that have key and value, Dict need the list sturct to be stored like a `list of dict` fashion.
@param head - The head of the list
*/
void displaydict(list *head);

/*
This function converts the given key and value by using malloc and assigns it to `dict *item` variable\n
this `dict *item` variable can then be used with the `append` function of list to append it to a list
*/
dict *creatitem(void *key, void *value);

/*
Returns the value which has the matching key as the one provided
@param dictlist - The given list should have dict sturct as it's data. compulsory
it will return NULL if there is no key matching with the one provided or if the dictlist is NULL\n
otherwise it will return the value
*/
void *getvaluefromkey(list *dictlist, void *key);

#endif
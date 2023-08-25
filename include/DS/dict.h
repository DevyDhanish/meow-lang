#ifndef DICT_H
#define DICT_H

#include "list.h"
#include <stdio.h>

typedef struct dict{
    void *key;
    void *value;
} dict;

// display
void displaydict(list *head);

// add item
dict *creatitem(void *key, void *value);

// get value from key
void *getvaluefromkey(list *dictlist, void *key);

#endif
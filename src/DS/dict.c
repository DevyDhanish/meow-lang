#include "../../include/DS/dict.h"
#include <stdio.h>
#include <stdlib.h>

void displaydict(list *head){
    if(head == NULL){
        printf("{}\n");
        return;
    }

    while(head != NULL){
        dict *item = head->data;
        printf("(%s, %s),", (char *)item->key, (char *)item->value);
        head = head->next;
    }
}

list *additem(list *dictlist, void *key, void *value){
    dict *item = (dict *) malloc(sizeof(dict));

    if(item == NULL){
        printf("Faild mem allocation for dict dict.c\n");
        return dictlist;
    }

    item->key = key;
    item->value = value;

    dictlist = append(dictlist, item);

    return dictlist;
}
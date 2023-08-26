#include "../../include/DS/dict.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displaydict(list *head){
    if(head == NULL){
        printf("()\n");
        return;
    }

    while(head != NULL){
        dict *item = (dict *)head->data;
        printf("(key : %s, value : %s)", (char *)item->key, (char *)item->value);
        head = head->next;
    }

    printf("\n");
}

dict *creatitem(void *key, void *value){
    dict *item = (dict *) malloc(sizeof(dict));

    if(item == NULL){
        printf("Faild mem allocation for dict dict.c\n"); 
        return NULL;
    }

    item->key = key;
    item->value = value;

    return item;
}

void *getvaluefromkey(list *dictlist, void *key){
    if(dictlist == NULL){
        printf("List is empty\n");
        return NULL;
    }

    while(dictlist != NULL){
        dict *item = (dict *) dictlist->data;

        if(strcmp((char *)item->key, key) == 0){
            return item->value;
        }

        dictlist = dictlist->next;
    }

    printf("No key found for %s", (char *)key);
    return NULL;
}
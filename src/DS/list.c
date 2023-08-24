#include "../../include/DS/list.h"
#include <stdio.h>
#include <stdlib.h>

void display(list *head){
    if(head == NULL){
        printf("[]\n");
        return;
    }

    while(head != NULL){
        printf("%s,", (char*)head->data);
        head = head->next;
    }
}

list *append(list *head, void *value_to_append){
    list *newNode = (list *) malloc(sizeof(list));
    newNode->data = value_to_append;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return head;
    }

    list *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;

    return head;
}
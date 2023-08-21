#include <stdio.h>
#include <stdlib.h>


#include "../include/ll/ll.h"

void display(Node *head){
    Node *temp = head;

    if(temp == NULL){
        printf("[]\n");
        return;
    }

    printf("[");
    while(temp != NULL){
        printf("%d", temp->data);
        temp = temp->next;

        if(temp != NULL){
            printf(",");
        }
    }

    printf("]");

    printf("\n");
}

Node *append(Node *head, int value){
    Node *newNode = (void*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return head;
    }

    while(head->next != NULL){
         head = head->next;
    }

    head->next = newNode;

    return head;
}

void insert(Node **head, int position, int value){
    Node *newNode = (void *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(position == 0){
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *temp = *head;

    for(int i = 0; i < position - 1 && temp != NULL; i++){
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

Node *removeN(Node *head, int value) {
    if (head == NULL)
        return head;

    if (head->data == value) {
        Node *newHead = head->next;
        free(head);
        return newHead;
    }

    Node *temp = head;

    while (temp->next != NULL) {
        if (temp->next->data == value) {
            Node *toRemove = temp->next;
            temp->next = temp->next->next;
            free(toRemove);
            return head;
        }
        temp = temp->next;
    }

    return head;
}

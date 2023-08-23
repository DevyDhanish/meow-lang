#include <stdio.h>
#include <stdlib.h>

#include "../include/ll/ll.h"

void display(Node *temp){

    if(temp == NULL){
        printf("[]\n");
        return;
    }

    printf("[");
    while(temp != NULL){
        printf("[%s]", temp->tok_data->type);
        temp = temp->tok_next;

        if(temp != NULL){
            printf(",");
        }
    }

    printf("]");

    printf("\n");
}

Node *append(Node *head, token *toattatch){
    Node *newNode = (void*)malloc(sizeof(Node));
    newNode->tok_data = toattatch;
    newNode->tok_next = NULL;

    if(head == NULL){
        head = newNode;
        return head;
    }

    while(head->tok_next != NULL){
         head = head->tok_next;
    }

    head->tok_next = newNode;

    return head;
}

// void insert(Node **head, token *to, int value){
//     Node *newNode = (void *)malloc(sizeof(Node));
//     newNode->data = value;
//     newNode->next = NULL;

//     if(position == 0){
//         newNode->next = *head;
//         *head = newNode;
//         return;
//     }

//     Node *temp = *head;

//     for(int i = 0; i < position - 1 && temp != NULL; i++){
//         temp = temp->next;
//     }

//     if(temp == NULL)
//     {
//         printf("Out of bounds\n");
//         free(newNode);
//         return;
//     }

//     newNode->next = temp->next;
//     temp->next = newNode;
// }

// Node *removeN(Node *head, int position) {
//     if (head == NULL)
//         return head;

//     if (head->tok_data == value) {
//         Node *newHead = head->next;
//         free(head);
//         return newHead;
//     }

//     Node *temp = head;

//     while (temp->next != NULL) {
//         if (temp->next->data == value) {
//             Node *toRemove = temp->next;
//             temp->next = temp->next->next;
//             free(toRemove);
//             return head;
//         }
//         temp = temp->next;
//     }

//     return head;
// }

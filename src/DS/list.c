#include "../../include/DS/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// int contains(list *head, void *type, void *value){
//     if(head == NULL){
//         printf("Given list is empty");
//         return 0;
//     }

//     while(head != NULL){
//         if(strcmp(type, "%c") == 0){
//             char a = *(char *)value;
//             printf("%c", a);
//             if((char)head->data == a){
//                 return 1;
//             }
//         }
//         if(strcmp(type, "%d") == 0){
//             if(head->data == (size_t *) value) return 1;
//         }

//         head = head->next;
//     }

//     return 0;
// }

list *append(list *head, void *value_to_append){
    list *newNode = (list *) malloc(sizeof(list));
    newNode->data = value_to_append;
    newNode->next = NULL;

    if(head == NULL){
        newNode->back = NULL;
        head = newNode;
        return head;
    }

    list *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    newNode->back = temp;
    temp->next = newNode;
    
    return head;
}
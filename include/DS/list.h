#ifndef LIST_H
#define LIST_H

// Structure of a single node
// linked list will contain
// list->list->list->null
typedef struct list{
    void *data;
    struct list *next;
}list;

// Displays the given list
// @param head of the list to display
void display(list *head);

// Appends something at the end of the list
// @param `head` the head of the list to append to
// @param `value_to_append` the value to append make sure to give it as &variable
// @returns the head of list with the new item attatched
list *append(list *head, void *value_to_append);

#endif
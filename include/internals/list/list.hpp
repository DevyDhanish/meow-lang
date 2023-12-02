#pragma once


typedef struct _node list;

struct _node
{
    void *data;
    list *next;
};

list *insert(list *, void *);

void display(list *);
#include "list.hpp"
#include "../mewcore_ast.hpp"
#include <stdlib.h>
#include <iostream>

list *insert(list *head, void * data)
{
    list *newNode = (list *) malloc(sizeof(list));

    if(!newNode)
    {
        std::cout << "Failed to allocate mem for new block\n";
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;

    if(!head)
    {
        head = newNode;
        return head;
    }

    list *temp = head;

    while(temp->next) { temp = temp->next; }

    temp->next = newNode;

    return head;
}

void display(list *head)
{
    if(!head)
    {
        std::cout << "Nothing to parse : ( Tree empty\n";
    }

    while(head)
    {
        stmt_ty *mod_data = (stmt_ty *)head->data;

        std::cout << "*************************\n";
        
        switch (mod_data->kind) // what kind of stmt is is
        {
        case _stmt_kind::Assign:
            displayAssignStmt(mod_data);
            break;
        
        default:
            break;
        }

        std::cout << "*************************\n";
        head = head->next;
    }
}
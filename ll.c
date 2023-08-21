#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node ;

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

Node *removeNthFromEnd(Node *head, int n) {
    if (head == NULL)
        return NULL;

    Node *dummy = (Node *)malloc(sizeof(Node)); // Create a dummy node to handle edge cases
    dummy->next = head;
    Node *fast = dummy;
    Node *slow = dummy;

    // Move fast pointer n+1 steps ahead
    for (int i = 1; i <= n + 1; i++) {
        fast = fast->next;
    }

    // Move both pointers together until fast reaches the end
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    // Remove the nth node from the end
    Node *toRemove = slow->next;
    slow->next = slow->next->next;
    free(toRemove);

    return dummy->next; // Return the updated head
}

Node *reverse(Node *head){
	Node *prev = NULL;
	Node *curr = head;
	Node *next = NULL;

	while(curr != NULL){

		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;

	}

	return prev;
}

int main(){
    Node *ll = NULL;

    display(ll);

    ll = append(ll, 1);
    ll = append(ll, 2);
    ll = append(ll, 3);
    ll = append(ll, 4);

	ll = reverse(ll);

    display(ll);
    return 0;
}

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// Function implementations for linked list operations...
// Inserts a node at the beginning of the linked list
Node *insertAtBeginning(Node *head, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL)
    {
        head->prev = newNode;
    }
    return newNode;
}

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
// Inserts a node at the end of the linked list
Node *insertAtEnd(Node *head, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL)
    {
        newNode->prev = NULL;
        return newNode;
    }
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return head;
}
// Inserts a node at a specific position in the linked list
Node *insertAtPosition(Node *head, int data, int position)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (position == 1)
    {
        newNode->next = head;
        if (head != NULL)
        {
            head->prev = newNode;
        }
        return newNode;
    }
    Node *current = head;
    for (int i = 1; i < position - 1 && current != NULL; i++)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        return insertAtEnd(head, data);
    }
    newNode->next = current->next;
    if (current->next != NULL)
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;

    return head;
}

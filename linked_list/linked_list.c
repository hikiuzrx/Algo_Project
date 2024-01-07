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
// Creates a copy of a linked list
Node *copyList(Node *head)
{
    Node *newHead = NULL;
    Node *tail = NULL;

    while (head != NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = head->data;
        newNode->next = NULL;
        newNode->prev = tail;

        if (newHead == NULL)
        {
            newHead = newNode;
        }
        else
        {
            tail->next = newNode;
        }

        tail = newNode;
        head = head->next;
    }

    return newHead;
}
// Performs insertion sort on the linked list, generating steps for visualization
void insertionSort(Node *originalHead, Node ***steps, int *stepCount)
{
    Node *sorted = NULL;
    Node *current = originalHead;

    *stepCount = 0;

    // Create an initial copy of the list to avoid modifying the original list
    Node *duplicate = copyList(originalHead);

    while (current != NULL)
    {
        Node *next = current->next;
        if (sorted == NULL || sorted->data >= current->data)
        {
            current->next = sorted;
            current->prev = NULL; // Update 'prev' pointer for the first node
            if (sorted != NULL)
            {
                sorted->prev = current; // Update 'prev' pointer for sorted list
            }
            sorted = current;
        }
        else
        {
            Node *temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            current->prev = temp;
            if (temp->next != NULL)
            {
                temp->next->prev = current;
            }
            temp->next = current;
        }

        // Store a copy of the current sorted list
        (*steps)[*stepCount] = copyList(sorted);
        (*stepCount)++;

        current = next;
    }

    // Free the duplicated list to avoid memory leaks
    while (duplicate != NULL)
    {
        Node *temp = duplicate;
        duplicate = duplicate->next;
        free(temp);
    }
}

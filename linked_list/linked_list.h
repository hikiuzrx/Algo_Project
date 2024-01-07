#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *insertAtBeginning(Node *head, int data);
Node *insertAtEnd(Node *head, int data);
Node *insertAtPosition(Node *head, int data, int position);
void deleteNodeWithValue(Node **head, int value);
void insertionSort(Node *originalHead, Node ***steps, int *stepCount);
void freeSteps(Node **steps, int stepCount);
Node *copyList(Node *head);

#endif /* LINKED_LIST_H */

// node.h
#ifndef NODE_H
#define NODE_H
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

void Create_Node(Node** h, int d);

#endif

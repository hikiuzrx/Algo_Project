#include "libraries/node.h"
void Create_Node(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        // If the list is empty, set the new node as the head
        *head = newNode;
    } else {
        // Otherwise, traverse the list and append the new node at the end
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void swapNodes(int* v1,int* v2){
     int temp = *v1;
     *v1= *v2;
     *v2 = *v1;
}
void insertionSort(Node** h){
     Node* swap = (*h)->next;
     while ((*h)->next!= NULL){
          if(swap->data < (*h)->data){
               int temp = swap->data;
               while(swap){
                    if(swap->data >temp){
                         swapNodes(&swap->data,&(swap->prv)->data);
                    }
                    swap =swap->prv;
               }
          }
          (*h)=(*h)->next;
          swap =(*h)->next;
     }
     
}

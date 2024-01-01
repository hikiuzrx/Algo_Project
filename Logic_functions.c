#include "node.h"
void Create_Node(Node**h,int d){
     if((*h)== NULL){
          (*h)= (Node*)malloc(sizeof(Node));
          (*h)->data = d;
          (*h)->prv = NULL;
          (*h)->next = NULL; 
     }else{
          Node* p =(Node*)malloc(sizeof(Node));
          (*h)->prv =p;
          p->next = (*h);
          (*h)=p;
     }
}
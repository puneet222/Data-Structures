#include<stdio.h>
#include<malloc.h>

struct list
{
  int data;
  struct list *next;
};


void push(struct list **head , int data , int pos)
{
    /* 1. allocate node */
    struct list* new_node = (struct list*) malloc(sizeof(struct list));
  
    /* 2. put in the data  */
    new_node->data  = data;
  
   if(pos == 1)
   {
   	 /* 3. Make next of new node as head */
    new_node->next = (*head);
  
    /* 4. move the head to point to the new node */
    (*head)    = new_node;
   }
}

void printList(struct list *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}

int main()
{
  /* Start with the empty list */
  struct list* head = NULL;
 
  // Insert 6.  So linked list becomes 6->NULL
  
 
  // Insert 7 at the beginning. So linked list becomes 7->6->NULL
  push(&head, 7 , 1);
 
  // Insert 1 at the beginning. So linked list becomes 1->7->6->NULL
  push(&head, 1 , 1);

  printList(head);

  return 0 ;

}
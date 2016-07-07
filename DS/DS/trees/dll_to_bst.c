#include<stdio.h>
#include<malloc.h>

struct list
{
	int data ;
	struct list *prev , *next ;
} ;

void insert(struct list **head , int data)
{
	struct list *newNode = malloc(sizeof(struct list)) ;
	newNode -> data = data ;
	newNode -> prev = NULL ;
	newNode -> next = NULL ;

	if(*head == NULL)
	{
		*head = newNode ;
		return ;
	}

	struct list *ptr ;
	ptr = *head ;
	while(ptr -> next != NULL)
	{
		ptr = ptr -> next ;
	}

	ptr -> next = newNode ;
	newNode -> prev = ptr ;
}

void display(struct list *head)
{
	while(head != NULL)
	{
		printf(" %d ", head -> data);
		head = head -> next ;
	}
}

struct list *getMiddle(struct list *head)
{
	if(head == NULL)
		return NULL ;
	if(head -> next == NULL)
		return head ;
	struct list *ptr , *pptr ;
	ptr = head ;
	pptr = head ;
	while(pptr -> next != NULL && pptr -> next -> next != NULL)
	{
		ptr = ptr -> next ;
		pptr = pptr -> next -> next ;
	}
	return ptr ;
}

void inorder(struct list *head)
{
	if(head)
	{
		
		inorder(head -> prev) ;
		printf(" %d ", head -> data);
		inorder(head -> next) ;
	}
}

void preorder(struct list *head)
{
	if(head)
	{
		printf(" %d ", head -> data);
		preorder(head -> prev) ;
		preorder(head -> next) ;
	}
}

struct list * dllToBST(struct list *head)
{
	if(head == NULL)
		return NULL ;
	if(head -> next == NULL)
		return head ;
	struct list *temp , *q , *p ;
	temp = getMiddle(head) ;
	q = temp -> next ;
	p = temp -> prev ;
	q -> prev = NULL ;
	if(p != NULL)
		p -> next = NULL ;
	else
	{
	printf("in lese\n");
	head = NULL ;
	}

	temp -> prev = NULL ;
	temp -> next = NULL ;
	printf("\nfirst list is \n");
	display(head) ;
	printf("\nsecond list is \n");
	display(q);
	temp -> prev = dllToBST(head) ;
	temp -> next = dllToBST(q) ;
	if(temp -> prev)
		printf("not null\n");
	else
		printf("null\n");
	inorder(temp) ;
	printf("\n");
	preorder(temp);

	return temp ;
}



int main()
{
	struct list *head = NULL ;
	int i ;
	for(i = 0 ; i < 10 ; i++)
	{
		insert(&head , i+1) ;
	}
	display(head);
	struct list *mid = getMiddle(head);
	printf("\n%d is the middle element \n", mid -> data );
	struct list *bst = dllToBST(head);
	printf("\nINORDER\n");
	inorder(bst);
}
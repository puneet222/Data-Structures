#include<stdio.h>
#include<malloc.h>
#include<limits.h>

struct node{
	int data ;
	struct node *left , *right ;
} ;

struct queue
{
	int front , rear ;
	int capacity ;
	struct node **array ;
};

struct queue *createQueue(int size)
{
	struct queue *Q = malloc(sizeof(struct queue)) ;
	if(!Q)
	{
		printf("creation of queue is not possible\n");
		return NULL ;
	}
	Q -> front = -1 ;
	Q -> rear = -1 ;
	Q -> capacity = size ;
	Q -> array = malloc(Q -> capacity * sizeof(struct node)) ;
	if(!Q -> array)
	{
		printf("creation of array of queue is not possible\n");
		return NULL ;
	}
	return Q ;
}

int isEmpty(struct queue *Q)
{
	return Q -> front == -1 ;
}

int isFull(struct queue *Q)
{
	return ((Q -> rear + 1) % Q -> capacity == Q -> front) ;
}

int getQSize(struct queue *Q)
{
	return (Q -> capacity - Q -> front + Q -> rear + 1) % Q -> capacity ;
}

void EnQueue(struct queue *Q , struct node *root)
{
	if(isFull(Q))
	{
		printf("Queue Overflow\n") ;
		return ;
	}
	Q -> rear = (Q -> rear + 1)%Q->capacity ;
	Q -> array[Q -> rear] = root ;
	if(Q -> front == -1)
	{
		Q -> front = Q -> rear ;
	} 
}

struct node *DeQueue(struct queue *Q)
{
	if(isEmpty(Q))
	{
		return NULL ;
	}
	else
	{
		struct node *d = Q -> array[Q -> front] ;
		
		if(Q -> front == Q -> rear) // one element in the queue
			Q -> front = Q -> rear = -1 ;
		else
			Q -> front = (Q -> front + 1) % Q -> capacity ;

		return d ;		
	}
	
}

int main()
{
	int i = 1, n ;
	printf("Enter the size of the queue\n");
	scanf("%d" , &n) ;
	struct queue *Q = createQueue(n) ;
	struct node *root = malloc(sizeof(struct node)) ;
	root -> data = 5 ;
	root -> left = NULL ;
	root -> right = NULL ;
	struct node *root1 = malloc(sizeof(struct node)) ;
	root -> data = 10 ;
	root -> left = NULL ;
	root -> right = NULL ;
	struct node *root2 = malloc(sizeof(struct node)) ;
	root -> data = 15 ;
	root -> left = root ;
	root -> right = root1 ;
	EnQueue(Q , root) ;
	EnQueue(Q , root1) ;
	int s = getQSize(Q) ;
	printf("sixe of queue is %d \n", s);
	
	printf("front is %d ", (Q -> array[Q -> front])->data);
	printf("rear is %d ", (Q -> array[Q -> rear]) -> data);
	
	// EnQueue(Q , root2) ;
	for(i = 0 ; i < 2 ; i++)
	{
		struct node *test = DeQueue(Q) ;
		printf(" %d\n", test -> data);
	}
}
#include<stdio.h>
#include<malloc.h>

struct node{
	int data ; 
	struct node *left , *right ;
} ;

struct list
{
	struct node *n ;
	struct list *next ;
};

struct queue
{
	struct list *front ;
	struct list *rear ;
};

struct queue *createQueue()
{
	struct queue *Q = malloc(sizeof(struct queue)) ;
	Q -> front = NULL ;
	Q -> rear = NULL ;
}

int isEmpty(struct queue *Q)
{
	if(Q -> front == NULL)
		return 1 ;
	else
		return 0 ;
}

void EnQueue(struct queue *Q , struct node *root)
{
	struct list *newNode = malloc(sizeof(struct list)) ;
	newNode -> next = NULL ;
	newNode -> n = root ;
	if(Q -> rear == NULL)
	{
		Q -> front = newNode ;
		Q -> rear = newNode ;
	}
	else
	{
		Q -> rear -> next = newNode ;
		Q -> rear = newNode ;
	}
	// printf("Inserted successsfully\n");
}

struct node *DeQueue(struct queue *Q)
{
	if(Q -> rear == NULL)
	{
		printf("Queue is Empty\n");
		return NULL ;
	}

	struct list *ptr ;
	ptr = Q -> front -> next ;
	struct node *root = Q -> front -> n ;
	if(Q -> front == Q -> rear)
	{
		free(Q -> front) ;
		Q -> front = NULL ;
		Q -> rear = NULL ;
		return root ;
	}
	Q -> front -> next = NULL ;
	free(Q -> front) ;
	Q -> front = ptr ;
	return root ;
}

void createBinaryTree(struct node *root , int data)
{
	struct node *newNode = malloc(sizeof(struct node)) ;
	newNode -> data = data ;
	newNode -> left = NULL ;
	newNode -> right = NULL ;

	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		if(p -> left)
			EnQueue(Q , p -> left) ;
		else
		{
			p -> left = newNode ;
			return ;
		}

		if(p -> right)
			EnQueue(Q , p -> right) ;
		else
		{
			p -> right = newNode ;
			return ;
		}
	}
}

void preorder(struct node *root)
{

}

void levelOrder(struct node *root)
{
	struct queue *Q = createQueue() ;
	EnQueue(root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		printf(" %d ", p -> data);
		if(p -> left)
			EnQueue(Q , p -> left) ;
		if(p -> right)
			EnQueue(p -> right) ;
	}
}

int main()
{
	int n ;
	struct node *root = malloc(sizeof(struct node)) ;
	printf("Enter the root elelment : ");
	scanf("%d",&n) ;
	root -> data = n ;
	root -> left = NULL ;
	root -> right = NULL ;

	int q = 1 ;
	while(q)
	{
		int c = 1;
		printf("Wnat to enter another elelment (0/1) : ");
		scanf("%d" , &c) ;
		if(c == 1)
		{
			printf("Enter data : ");
			scanf("%d" , &n) ;
			createBinaryTree(root , n) ;
		}
		else
		{
			break ;
		}
	}

	levelOrder(root) ;
}
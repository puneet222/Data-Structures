#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>


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

struct arrayStack
{
	int top ; 
	int capacity ;
	struct node **array ;
};

struct arrayStack *createStack(int size)
{
	struct arrayStack *S = malloc(sizeof(struct arrayStack)) ;
	S -> top = -1 ;
	S -> capacity = size ;
	S -> array = malloc(sizeof(struct node)*S->capacity) ;
	return S ;
}

int isStackEmpty(struct arrayStack *S)
{
	return (S -> top == -1) ;
}

int isStackFull(struct arrayStack *S)
{
	return (S -> top == (S -> capacity)-1) ;
}

struct node *pop(struct arrayStack *S)
{
	if(isStackEmpty(S))
	{
		printf("Array is Empty\n");
		return 0;
	} 
	else
	{
		struct node *data = S->array[S->top] ;
		S-> top-- ;
		return data ;
	}
}

void push(struct arrayStack *S, struct node *root)
{
	if(isStackFull(S))
	{
		printf("StackOverflow\n");
		return ;
	}
	else
	{
		S->array[++S->top] = root ;
		// printf("Inserted Successfully\n");
	}
}

void preorder(struct node *root)
{
	struct arrayStack *S = createStack(15) ; 
	push(S , root) ;
	while(!isStackEmpty(S))
	{
		struct node *p = pop(S) ;
		printf(" %d ", p -> data );
		
		if(p -> right)
			push(S , p -> right) ;

		if( p -> left)
			push(S , p -> left) ;
	}
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



void levelOrder(struct node *root)
{
	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		printf(" %d ", p -> data);
		if(p -> left)
			EnQueue(Q , p -> left) ;
		if(p -> right)
			EnQueue(Q , p -> right) ;
	}
}

struct node *mirrorTree(struct node *root)
{
	struct node *temp ;
	if(root)
	{
		temp = root -> left ;
		root -> left = root -> right ;
		root -> right = temp ;
		mirrorTree(root -> left) ;
		mirrorTree(root -> right) ;
	}
	return root ;

}

struct node *LCA(struct node *root , struct node *n1 , struct node *n2)
{
	if(root == NULL)
		return root ;
	if(root == n1 || root == n2)
		return root ;
	struct node *left , *right ;
	left = LCA(root -> left , n1 , n2) ;
	right = LCA(root -> right , n1 , n2) ;
	if(left && right)
		return root ;
	else
		return (left ? left : right) ;
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

	levelOrder(root) ; 															// level order traversal
	printf("\n\nPreorder : \n");
	preorder(root) ;   															// preorder traversal
	struct node *mirror = mirrorTree(root) ;									// Finding the mirror of the tree
	printf("\n");
	printf("Preorder of mirror tree\n");
	preorder(mirror) ;															

	printf("\nLevel order of mirror tree\n");
	levelOrder(mirror) ;

	struct node *lca = LCA(root , root -> left , root -> right) ;
	printf("\n\nlca is %d\n", lca -> data);             // Least Common Ancestor
}
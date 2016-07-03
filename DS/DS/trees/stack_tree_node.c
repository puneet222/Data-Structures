#include<stdio.h>
#include<malloc.h>

struct node
{
	int data ;
	struct node *left , *right ;
};

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

int isEmpty(struct arrayStack *S)
{
	return (S -> top == -1) ;
}

int isFull(struct arrayStack *S)
{
	return (S -> top == (S -> capacity)-1) ;
}

struct node *pop(struct arrayStack *S)
{
	if(isEmpty(S))
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
	if(isFull(S))
	{
		printf("StackOverflow\n");
		return ;
	}
	else
	{
		S->array[++S->top] = root ;
		printf("Inserted Successfully\n");
	}
}

int main()
{
	struct arrayStack *S = createStack(3) ;
	//now we have a stack of size 3 ;
	struct node *root = malloc(sizeof(struct node)) ;
	root -> data = 5 ;
	root -> left = NULL ;
	root -> right = NULL ;
	push(S , root) ;
	struct node *test = pop(S);
	printf(" %d \n", test -> data);
}
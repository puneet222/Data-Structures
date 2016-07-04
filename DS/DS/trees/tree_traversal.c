#include<stdio.h>
#include<malloc.h>

struct node{
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
		// printf("Inserted Successfully\n");
	}
}

struct node *createTree(int post[] , int in[] , int n , int t )
{
	printf("Execution number %d\n", t);
	int q = ++t ;
	int rootc = post[n-1] ;
	struct node *root = malloc(sizeof(struct node)) ;
	root -> data = rootc ;
	if(n == 0)
		return NULL ;
	if(n < 2)
	{
		printf("I'm in if\n");
		root -> left = NULL ;
		root -> right = NULL ;
		return root ;
	}
	int newpost[10] , newin[10] , newpostr[10] , newinr[10];
	int l = 0 , i ;
	for(i = 0 ; i < n ; i++)
	{
		
		if(in[i] != rootc)
		{
			l++ ;
			newin[i] = in[i] ;
			newpost[i] = post[i] ;
		}
		else
		{
			break ;
		}
	}
	int r =0 ;

	for(i = l ; i < n-1 ; i++) 
	{
		r++ ;
		newinr[i-l] = in[i+1] ;
		newpostr[i-l] = post[i] ;
	}

	// printf(" %d 2nd element of inorder\n%d is 2nd element of post\nlength is %d\n",newin[0] , newpost[0] , l );
	
	root -> left = createTree(newpost , newin , l , q);
	root -> right = createTree(newpostr , newinr , r , q);

	return root ;

}

void preorder(struct node *root)
{
	if(root)
	{
		printf(" %d  ", root -> data);
		preorder(root -> left) ;
		preorder(root -> right) ;
	}
	// printf("\n");
}

void nonRecursivePreorder(struct node *root)
{
	struct arrayStack *S = createStack(8) ;
	while(1)
	{
		while(root)
		{
			printf(" %d ", root -> data);
			push(S , root) ;
			root = root -> left ;
		}
		if(isEmpty(S))
			break ;
		root = pop(S) ;
		root = root -> right ;
	}
}

void inorder(struct node *root)
{
	if(root)
	{
		inorder(root -> left) ;
		printf(" %d  ", root -> data);
		inorder(root -> right) ;
	}
}

void nonRecursiveInorder(struct node *root)
{
	struct arrayStack *S = createStack(8) ;
	while(1)
	{
		while(root)
		{
			push(S , root) ;
			root = root -> left ;
		}
		if(isEmpty(S))
			break ;
		root = pop(S) ;
		printf(" %d ", root -> data);
		root = root -> right ;
	}
}

void postorder(struct node *root)
{
	if(root)
	{
		postorder(root -> left) ;
		postorder(root -> right) ;
		printf(" %d ", root -> data);
	}
}


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

// void display(struct queue *Q)
// {
// 	struct list *ptr = Q -> front ;
// 	while(ptr != NULL)
// 	{
// 		printf(" %d ", ptr -> data);
// 		ptr = ptr -> next ;
// 	}
// }




void levelOrder(struct node *root)
{
	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;

	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		if(p -> left)
			{
				EnQueue(Q , p -> left) ;
			}

		if(p -> right)
			EnQueue(Q , p -> right) ;

		printf(" %d ", p -> data);

		// printf(" %d ewklmvcoiewvm\n", isEmpty(Q));
	}
}



int main()
{
	int in[] = {4,8,2,5,1,6,3,7} ;
	int post[] = {8,4,5,2,6,7,3,1} ;

	int n = 8 ;
	int t = 1 ;
	struct node *root = createTree(post , in , n, t) ;
	// printf(" %d \n", root->left->right->data);
	printf("\nPREOREDER TRAVERSAL--------------\n\n\n\n");
	preorder(root);
	printf("\nNON recursive preorder\n");
	nonRecursivePreorder(root) ;
	printf("\n\nINOREDER TRAVERSAL--------------\n\n\n\n");
	inorder(root);
	printf("\nNON recursive inorder\n");
	nonRecursiveInorder(root) ;
	printf("\n\nPOSTOREDER TRAVERSAL--------------\n\n\n\n");
	postorder(root);
	// printf("\nNON recursive postorder\n");
	// nonRecursivePostorder(root) ;
	printf("\nLEVEL ORDER TRAVERSAL--------------\n");
	levelOrder(root);
}
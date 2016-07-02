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

int BinaryTreeSize(struct node *root){
	if(root == NULL)
		return 0 ;
	else
		return (BinaryTreeSize(root -> left) + 1 + BinaryTreeSize(root -> right)) ;
}

void reverseLevelOrder(struct node *root)
{
	struct queue *Q = createQueue() ; 
	struct arrayStack *S = createStack(15) ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		push(S , p) ;
		if(p -> right)
			EnQueue(Q , p -> right) ;
		if(p -> left)
			EnQueue(Q , p -> left) ;
	}
	while(!isStackEmpty(S))
	{
		struct node *p = pop(S) ;
		printf(" %d ", p -> data);
	}
}

struct node *deepestNode(struct node *root)
{
	struct queue *Q = createQueue() ; 
	struct node *p = NULL ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		p = DeQueue(Q) ; 
		if(p -> left)
			EnQueue(Q , p -> left) ;
		if(p -> right)
			EnQueue(Q , p -> right) ;
	}
	return p ;
}

int power(int base , int power)
{
	int result = 1 ;
	int i ;
	for(i = 0 ; i < power ; i++)
	{
		result = result * base ;
	}
	return result ;
}

int heightOfBT(struct node *root)
{
	int size = BinaryTreeSize(root) ;
	int i = 0 , sum = 0;
	while(1)
	{
		sum = sum + power(2,i) ;
		if(size <= sum)
		{
			return i ;
		}
		i++ ;
	}
}

int heightWithRecursion(struct node *root)
{
	int leftH , rightH ;
	if(root == NULL)
		return 0 ;
	else
	{
		leftH = heightWithRecursion(root -> left) ;
		rightH = heightWithRecursion(root -> right) ;
		if(leftH > rightH)
			return (leftH + 1) ;
		else
			return rightH + 1 ;
	}
}

int numberOfLeafNodes(struct node *root)
{
	int leaf = 0 ;
	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		if(p -> left == NULL && p -> right == NULL)
		{
			leaf++ ;
			continue ;
		}
		else
		{
			if(p -> left)
				EnQueue(Q , p -> left) ;

			if(p -> right)
				EnQueue(Q , p -> right) ;
		}
	}
	return leaf ;
}

int numberOfFullNodes(struct node *root)
{
	int full = 0 ;
	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		if(p -> left != NULL && p -> right != NULL)
		{
			full++ ;
		}
		
			if(p -> left)
				EnQueue(Q , p -> left) ;

			if(p -> right)
				EnQueue(Q , p -> right) ;
		
	}
	return full ;
}

int numberOfHalfNodes(struct node *root)
{
	int half = 0 ;
	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;
	while(Q -> front)
	{
		struct node *p = DeQueue(Q) ;
		if((p -> left == NULL && p -> right != NULL)||(p -> left != NULL && p -> right == NULL))
		{
			half++ ;
		}
		
			if(p -> left)
				EnQueue(Q , p -> left) ;

			if(p -> right)
				EnQueue(Q , p -> right) ;
		
	}
	return half ;
}

int areStructureSame(struct node *root1 , struct node *root2)
{
	if(root2 == NULL && root1 == NULL)
		return 1 ;
	if(root1 == NULL || root2 == NULL)
		return 0 ;
	return ((root1 -> data == root2 -> data)&& areStructureSame(root1 -> left , root2 -> left) && areStructureSame(root1 -> right , root2 -> right)) ;
}

int max(int a, int b)
{
  return (a >= b)? a: b;
} 

int diameterOfBT(struct node *root)
{
	if(root == NULL)
		return 0 ;

	int lheight = heightWithRecursion(root -> left) ;
	int rheight = heightWithRecursion(root -> right) ;

	int ldiameter = diameterOfBT(root -> left) ;
	int rdiameter = diameterOfBT(root -> right) ;

	return max((lheight + rheight + 1) , max(rdiameter , ldiameter)) ;
}

void maxlevelSum(struct node *root)
{
	int maxSum = INT_MIN , sumlevel = 0 , level = 0 , maxlevel;
	struct queue *Q = createQueue() ;
	EnQueue(Q , root) ;
	EnQueue(Q , NULL) ;
	while(Q -> front)
	{
		// printf("In white\n");
		struct node *temp = DeQueue(Q) ;
		if(temp == NULL) // break point next level
		{
			if(sumlevel > maxSum)
			{
				maxSum = sumlevel ;
				maxlevel = level ;
			}
			sumlevel = 0 ;
			if(Q -> front)
				EnQueue(Q , NULL) ;
			level++ ;
		}
		else
		{
			sumlevel += temp -> data ;
		if(temp ->left)
			EnQueue(Q , temp -> left) ;
		if(temp -> right)
			EnQueue(Q , temp -> right) ;
		}

	}
	printf("MAX sum at level is %d\n", maxSum);
	printf("Level Number is %d\n", maxlevel);
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
	printf("\n\nSize if the tree is %d", BinaryTreeSize(root));
	printf("\n\n\nReverse level order traversal is :\n");
	reverseLevelOrder(root); 													 // reverse level order traversal

	struct node *deepNode = deepestNode(root) ;
	printf("\nDeepest node of the tree is : %d \n", deepNode -> data);

	printf("Height of the tree is  : %d \n",heightOfBT(root) );  				// height of binary tree meeeee

	int h = heightWithRecursion(root) ;   										// height of binary tree with recursion
	printf("%d\n", h);

	int leaf = numberOfLeafNodes(root) ;   										// number of leaf nodes
	printf("Number of leaf nodes of the tree are : %d\n",leaf );

	int full = numberOfFullNodes(root);											// number of full nodes
	printf("Number of full nodes in the tree are : %d\n",full );

	int half = numberOfHalfNodes(root) ;										// number of half nodes
	printf("Number of half nodes in the tree are : %d\n",half );

	struct node *root1 = malloc(sizeof(struct node)) ;     //-------------- are structural same two trees
	printf("Enter the root elelment : ");
	scanf("%d",&n) ;
	root1 -> data = n ;
	root1 -> left = NULL ;
	root1 -> right = NULL ;

	while(1)
	{
		int c = 1;
		printf("Want to enter another elelment (0/1) : ");
		scanf("%d" , &c) ;
		if(c == 1)
		{
			printf("Enter data : ");
			scanf("%d" , &n) ;
			createBinaryTree(root1 , n) ;
		}
		else
		{
			break ;
		}
	}

	if(areStructureSame(root , root1))
		printf("Both the trees are structural same\n");
	else
		printf("Trees are not strictural same\n");

	int diameter = diameterOfBT(root) ;											// diameter or width of the tree
	printf("Diameter of the tree is : %d\n", diameter );

	maxlevelSum(root) ;

}
#include<stdio.h>
#include<malloc.h>

struct node{
	char data ;
	struct node *left , *right ;
} ;

struct node *BuildTree(char *arr , int *n)
{
	if(arr == NULL)
		return NULL ;
	// printf("value of  n is %d\n", *n );
	struct node *newNode = malloc(sizeof(struct node)) ;
	newNode -> data = arr[*n] ;
	newNode -> left = NULL ;
	newNode -> right = NULL ;

	if(arr[*n] == 'L')
		{
			// printf("found leaf node\n");
			return newNode ;

		}
	*n = *n + 1 ;
	// printf("\n%d is passed to left\n", *n );
	newNode -> left = BuildTree(arr , n) ;

	*n = *n + 1 ;
	// printf("\n%d is passed to right\n", *n );
	newNode -> right = BuildTree(arr , n) ; 
}

void preorder(struct node *root)
{
	if(root)
	{
		printf(" %c ", root -> data);
		preorder(root -> left) ;
		preorder(root -> right) ;
	}
}

int main()
{
	char *arr = "IIILLLILIILLL" ;
	int n = 0 ;
	struct node *res = BuildTree(arr , &n) ;
	preorder(res) ;
}
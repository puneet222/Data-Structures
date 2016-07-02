#include<stdio.h>
#include<malloc.h>

struct node{
	int data ;
	struct node *left , *right ;
};

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
}


int main()
{
	int in[] = {4,8,2,5,1,6,3,7} ;
	int post[] = {8,4,5,2,6,7,3,1} ;

	int n = 8 ;
	int t = 1 ;
	struct node *root = createTree(post , in , n, t) ;
	// printf(" %d \n", root->left->right->data);
	preorder(root);
}
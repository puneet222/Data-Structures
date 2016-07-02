#include<stdio.h>
#include<malloc.h>
#include<iostream>
#include<queue>
#include<stack>

using namespace std ;


stack<struct node *> S ;

struct node{
	int data ;
	struct node *left , *right ;
};

int getIndex(int *in , int pre , int n)
{
	int i ;
	for(i = 0 ; i < n ; i++)
	{
		if(in[i] == pre)
			return i ;
	}
	return 0 ;
}

struct node *BuildTree(int *in , int *pre , int n)
{




	if(n == 0)
		return NULL ;


	struct node *root = (struct node *)malloc(sizeof(struct node)) ;
	int rn = pre[0] ;
	root -> data = rn ;
	// printf("\n %d is the root data\n", root -> data );
	int ind = getIndex(in , rn , n);
	// printf("Index is %d\n", ind);
	int inl[n/2] , prel[n/2] , inr[n/2] , prer[n/2] , l = 0 , r = 0 , i;
	for(i = 0 ; i < ind ; i++)
	{
		inl[i] = in[i] ;
		l++ ;
	}
	for(i = 1 ; i <= ind ; i++)
	{
		prel[i-1] = pre[i] ;
	}

	


	for(i = ind + 1 ; i < n ; i++)
	{
		inr[i-(ind+1)] = in[i] ;
		prer[i-(ind + 1)] = pre[i] ;
		r++ ;
	}

	// printf("\nindex is %d and n is %d and l is %d and r is %d \n",ind , n , l , r);


	// printf("Value of l is %d & Value of r is %d\n", l , r);
	// printf("in left\n");
	root -> left = BuildTree(inl , prel , l) ;
	// printf("in right\n");
	root -> right = BuildTree(inr , prer , r) ;


	return root ;
}

void preorder(struct node *root)
{
	if(root)
	{
		printf(" %d ", root -> data);
		preorder(root -> left) ;
		preorder(root -> right) ;
	}
}

void inorder(struct node *root)
{
	if(root)
	{
		
		preorder(root -> left) ;
		printf(" %d ", root -> data);
		preorder(root -> right) ;
	}
}
int printAllAncestors(struct node *root , struct node *tnode)
{
	if(root == NULL)
		return 0 ;
	if(root -> left == tnode || root -> right == tnode || printAllAncestors(root -> left , tnode) || printAllAncestors(root -> right , tnode) )
	{
		printf(" %d ", root -> data);
		return 1 ;
	}
	return 0 ;
}

void zigzag(struct node *root)
{
	if(root == NULL)
		return ;

queue<struct node *> Q ;
	Q.push(root) ;
	Q.push(NULL) ;
	int r = 1 ;
	printf("\n%d " , root -> data);
	struct node *temp , *ptr;
	while(1)
	{
			temp = Q.front() ;
			Q.pop() ;
			if(temp == NULL)
			{
				// printf("\n\n%d is the size of the queue\n", (int)Q.size());
				Q.push(NULL) ;
				if(r == 0)
					r = 1 ;
				else
					r = 0 ;

				if(r == 1)
				{
					// printf("\nleft to right\n");
					ptr = Q.front() ;
					Q.pop() ;
					while(ptr != NULL)
					{
						printf(" %d", ptr -> data);
						Q.push(ptr) ;
						ptr = Q.front() ;
						Q.pop() ;
					}
					temp = Q.front() ;
					Q.pop() ;
				}

				if(r == 0)
				{
					// printf("\nright to left\n");
					ptr = Q.front() ;
					Q.pop() ;
					while(ptr != NULL)
					{
						// printf("in left vala loop\n");
						S.push(ptr) ;
						Q.push(ptr) ;
						ptr = Q.front() ;
						Q.pop() ;
					}
					while(!S.empty())
					{
						// printf("in stack loop\n");
						ptr = S.top() ;
						printf(" %d ", ptr -> data);
						S.pop() ;
					}
					temp = Q.front() ;
					Q.pop() ;
					
				}
				Q.push(NULL);
			}
			else
			{
				// printf(" %d is is thw temp dtaa\n", temp -> data );
			}
			if(Q.empty())
			{
				break ;
			}

			if(temp -> left)
			{
				Q.push(temp -> left) ;
				// printf("\n\n%d this data is inserted into queue\n", temp -> left -> data);
			}

			if(temp -> right)
			{
				// printf("%d this data is inserted into queue\n", temp -> right -> data);
				Q.push(temp -> right) ;
			}
	}
}

void printArr(int *path , int len)
{
	for (int i = 0; i < len; ++i)
	{
		cout << path[i] << " " ;
	}
	printf("\n");
}

void rootToLeaf(struct node *root , int *path , int pathlen)
{
	if(root == NULL)
		return ;
	path[pathlen] = root -> data ;
	pathlen++ ;
	if(root -> left == NULL && root -> right == NULL)
		printArr(path , pathlen) ;
	rootToLeaf(root -> left , path , pathlen) ;
	rootToLeaf(root -> right , path , pathlen) ;
}

int hasPathSum(struct node *root , int sum)
{
	if(root == NULL)
		return (sum == 0) ;
	else
	{
		int ans = 0 ;

		sum = sum - root -> data ;

		if(sum == 0 && root -> left == NULL && root -> right == NULL)
			return 1 ;

		if(root -> left)
			ans = ans || hasPathSum(root -> left , sum) ;
		if(root -> right)
			ans = ans || hasPathSum(root -> right , sum) ;

		return ans ;
	}
}



int main()
{
	// int in[] = {4,2,5,1,6,3,7} ;
	// int pre[] = {1,2,4,5,3,6,7} ;
	int in[] = {8,4,9,2,10,5,11,1,12,6,13,3,14,7,15} ;
	int pre[] = {1,2,4,8,9,5,10,11,3,6,12,13,7,14,15} ;
	int n = 15 ;
	
	struct node *root = BuildTree(in , pre , n) ;  							// build tree with inorder and preorder
	preorder(root) ;
	printf("\n");
	inorder(root);
	printf("\nancestors are : \n");
	printAllAncestors(root , root -> right -> right) ; 						// print all the ancestors of the node 
	zigzag(root);															// ZIGZAG printing of the level order
	printf("\n\n\nRoot to node paths\n");

	int path[10] ;

	rootToLeaf(root , path , 0 ) ;											// root to leaf paths 
	if(hasPathSum(root , 15))
		printf("THERE exists a path\n");
	else
		printf("NO PATH EXISTS\n");
}
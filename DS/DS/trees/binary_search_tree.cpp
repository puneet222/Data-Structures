#include<iostream>
#include<stack>
#include<queue>
#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include<vector>
using namespace std ;

struct node{
	int data ;
	struct node *left , *right ;
} ;

void insertInBST(struct node **root , int data)
{
	struct node *newNode = new node ;
	newNode -> data = data ;
	newNode -> left = NULL ;
	newNode -> right = NULL ;

	if(*root == NULL)
	{
		*root = newNode ;
		return ;
	}

	struct node *ptr ;
	ptr = *root ;
		while(1)
		{
			if(data < ptr -> data)
			{
				if(ptr -> left == NULL)
				{
					ptr -> left = newNode ;
					break ;
				}
				ptr = ptr -> left ;
			}
			else
			{
				if(ptr -> right == NULL)
				{
					ptr -> right = newNode ;
					break ;
				}
				ptr = ptr -> right ;
			}
		}
}

struct node *findMin(struct node *root)
{
	if(root == NULL)
		return NULL ;
	while(root -> left != NULL)
		root = root -> left ;
	return root ;
}

struct node *findMinRecursive(struct node *root)
{
	if(root == NULL)
		return NULL ;
	if(root -> left == NULL)
		return root ;
	else
		findMinRecursive(root -> left) ;
}

struct node *findMax(struct node *root)
{
	if(root == NULL)
		return NULL ;
	while(root -> right != NULL)
		root = root -> right ;
	return root ;
}

struct node *findMaxRecursive(struct node *root)
{
	if(root == NULL)
		return NULL ;
	if(root -> right == NULL)
		return root ;
	else
		findMaxRecursive(root -> right) ;
}

struct node *insertInBSTRecursive(struct node *root , int data)
{

	if(root == NULL)
	{
		struct node *newNode = new node ;
		newNode -> data = data ;
		newNode -> left = NULL ;
		newNode -> right = NULL ;
		return newNode ;
	}

	if(data < root -> data)
		root -> left = insertInBSTRecursive(root -> left , data) ;
	else
		root -> right = insertInBSTRecursive(root -> right , data) ;
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

struct node *findInBST(struct node *root , int data)
{
	if(root == NULL)
		return NULL ;

	while(root)
	{
		if(data < root -> data)
		{
			if(data == root -> data)
				return root ;
			root = root -> left ;
		}
		else
		{
			if(data == root -> data)
				return root ;
			root = root -> right ;
		}
	}
}

struct node *findInBSTRecursive(struct node *root , int data)
{
	if(root == NULL)
		return NULL ;

	if(data == root -> data)
	{
		return root ;
	}

	if(data < root -> data)
		findInBSTRecursive(root -> left , data) ;
	else
		findInBSTRecursive(root -> right , data) ;
}

struct node *deleteFromBST(struct node *root , int data)
{
	struct node *temp ;
	if(root == NULL)
	{
		cout << "Element Not Found \n" ;
		return NULL ;
	}
	if(data < root -> data)
		root -> left = deleteFromBST(root -> left , data) ;
	else if(data > root -> data)
		root -> right = deleteFromBST(root -> right , data);
	else
	{
		cout << "\nElement found" ;
		if(root -> left && root -> right)
		{
			temp = findMax(root -> left) ;	
			root -> data = temp -> data ;
			root -> left = deleteFromBST(root -> left , root -> data) ;
		}
		else if( (root -> left == NULL && root -> right != NULL )||(root -> left != NULL && root -> right == NULL) )
		{
			cout << "IN else\n\n" ;
			temp = root ;
			if(root -> left == NULL)
				root = root -> right ;
			if(root -> right == NULL)
				root = root -> left ;
			free(temp) ;
		}
		else
		{
			free(root) ;
		}
	}
	return root ;
}

struct node *findLCA(struct node *root , struct node *n1 , struct node *n2)
{
	if(root == NULL)
		return NULL ;
	while(1)
	{
		if( (root -> data < n1 -> data && root -> data > n2 -> data) || ( root -> data > n1 -> data && root -> data < n2 -> data ))
			return root ;
		if(root -> data > n1 -> data)
			root = root -> left ;
		else
			root = root -> right ;
	}
}

int IsBST(struct node *root)
{
	if(root == NULL)
		return 1 ;
	if(root -> left != NULL && root -> left -> data > root -> data)
		return 0 ;
	if(root -> right != NULL && root -> right -> data < root -> data)
		return 0 ;
	if(!IsBST(root -> left) || !IsBST(root -> right))
		return 0 ;

	return 1 ;
}

int IsBSTUtil(struct node *root , int min , int max)
{
	if(root == NULL)
		return 1 ;

	return (root -> data > min && root -> data < max && IsBSTUtil(root -> left , min , root -> data) && IsBSTUtil(root -> right , root -> data , max)) ;
}

vector <int> v ;

int isBSTMy(struct node *root , int *prev)
{
		if(!root)
			return 1 ;

		if(!isBSTMy(root -> left , prev))
			return 0 ;

		if(root -> data < *prev)
			{
				printf("not increaing\n");
				printf("%d is the latesst data nad %d is the prev dara\n", root -> data , *prev);
				return 0 ;
			}

		printf("%d is the previous element \n", *prev );

		*prev = root -> data ;
		if(isBSTMy(root -> right , prev))
			return 1 ;
		else
			return 0 ;
		
}

int newIsBST(struct node *root)
{
	if(root)
	{
		newIsBST(root -> left) ;
		if(v.empty())
			v.push_back(root -> data) ;
		else
		{
			int c = v.front() ;
			if(c > root -> data)
				return 0 ;
			v.pop_back() ;
			v.push_back(root -> data) ;
		}
		(newIsBST(root -> right)) ;

	}
	else
		return 1 ;
}

void rangePrinter(struct node *root , int k1 , int k2)
{
	queue <struct node *> Q ;
	Q.push(root) ;
	while(!Q.empty())
	{
		struct node *ptr = Q.front() ;
		Q.pop() ;
		if(ptr -> data >= k1 && ptr -> data <= k2)
			printf(" %d ", ptr -> data);
		if(ptr -> left)
			Q.push(ptr -> left) ;
		if(ptr -> right)
			Q.push(ptr -> right) ;
	}
}

int sameBST(struct node *root1 , struct node *root2)
{
	if(root1 == NULL && root2 == NULL)
		return 1 ;
	if(root1 -> data != root2 -> data)
		return 0 ;

	if( (root1 == NULL && root2 != NULL) || (root1 != NULL && root2 == NULL) )
		return 0 ;
	return (sameBST(root1 -> left , root2 -> left) && sameBST(root1 -> right , root2 -> right)) ;
}

int kthSmallestElement(struct node *root , int k , int *count)
{
	if(root)
	{
		kthSmallestElement(root -> left , k , count) ;
		if(++(*count) == k)
			{
				printf("%d is the root data\n", root -> data);
				return root -> data ;
			}
		kthSmallestElement(root -> right , k , count) ;
	}
}

struct node *arrayToBST(int *arr , int li, int ri)
{
	if(li> ri)
		return NULL ;
	struct node *newNode = new node ;
	if(li == ri)
	{
		newNode -> data = arr[li] ;
		newNode -> left = NULL ;
		newNode -> right = NULL ;
		return newNode ;
	}
	int mid = (ri + li)/2 ;
	newNode -> data = arr[mid] ;
	newNode -> left = arrayToBST(arr , li , mid-1) ;
	newNode -> right = arrayToBST(arr , mid + 1 , ri) ;
	return newNode ;
}


int main()
{
	struct node *root = NULL ;
	int t = 10 ;
	insertInBST(&root , t) ;
	insertInBST(&root , 7) ;
	insertInBST(&root , 15) ;
	insertInBST(&root , 5) ;
	insertInBST(&root , 8) ;
	insertInBST(&root , 13) ;
	insertInBST(&root , 17) ;
	insertInBST(&root , 9) ;
	
	preorder(root) ;

	struct node *root2 = NULL ;
	root2 = insertInBSTRecursive(root2 , 10) ;
	root2 = insertInBSTRecursive(root2 , 7) ;
	root2 = insertInBSTRecursive(root2 , 15) ;
	root2 = insertInBSTRecursive(root2 , 5) ;
	root2 = insertInBSTRecursive(root2 , 8) ;
	root2 = insertInBSTRecursive(root2 , 13) ;
	root2 = insertInBSTRecursive(root2 , 17) ;
	root2 = insertInBSTRecursive(root2 , 9) ;
	root2 = insertInBSTRecursive(root2 , 14) ;
	root2 = insertInBSTRecursive(root2 , 6) ;

	struct node *root3 = NULL ;
	root3 = insertInBSTRecursive(root3 , 10) ;
	root3 = insertInBSTRecursive(root3 , 7) ;
	root3 = insertInBSTRecursive(root3 , 15) ;
	root3 = insertInBSTRecursive(root3 , 4) ;
	root3 = insertInBSTRecursive(root3 , 8) ;
	root3 = insertInBSTRecursive(root3 , 13) ;
	root3 = insertInBSTRecursive(root3 , 17) ;
	root3 = insertInBSTRecursive(root3 , 9) ;
	root3 = insertInBSTRecursive(root3 , 14) ;
	root3 = insertInBSTRecursive(root3 , 6) ;

	printf("%d\n", root2 -> data);
	printf("\n");
	preorder(root2);

	struct node *node1 = findInBST(root , 8) ;
	printf("\n %d is searched element in the BST\n", node1 -> data);

	struct node *node2 = findInBSTRecursive(root2 , 14) ;
	printf("\n %d is searched element in the BST\n", node2 -> data);

	struct node *min1 = findMin(root) ;
	printf("\n %d is the minimum element in the BST\n", min1 -> data);

	struct node *min2 = findMinRecursive(root2) ;
	printf("\n %d is the minimum element in the BST\n", min2 -> data);

	struct node *max1 = findMax(root) ;
	printf("\n %d is the maximum element in the BST\n", max1 -> data);

	struct node *max2 = findMaxRecursive(root2) ;
	printf("\n %d is the maximum element in the BST\n", max2 -> data);

	struct node *n1 = root2 -> right -> left -> right ;
	struct node *n2 = root2 -> right -> right ;

	struct node *lca = findLCA(root2 , n1 , n2) ;
	printf("\nlca is %d\n", lca -> data);

	// struct node *testroot = root2 ;
	// testroot -> right -> right -> data = 3 ;
	// testroot -> right -> left -> right -> data = 3 ;
	

	if(IsBST(root2))
		printf("\nIt is a binary search tree\n");
	else
		printf("\nAlthough it is binary tree but not Binary Search Tree\n");

	int m = INT_MIN ;
	if(isBSTMy(root2 , &m))
		printf("BST\n");
	else
		printf("BT\n");

	if(newIsBST(root2))
		printf("BST\n");
	else
		printf("BT\n");

	if(IsBSTUtil(root2 , INT_MIN , INT_MAX))
		printf("\nIt is a binary search tree\n");
	else
		printf("\nAlthough it is binary tree but not Binary Search Tree\n");

	rangePrinter(root2 , 8 , 15) ;

	if(sameBST(root2 , root2))
		printf("\nBoth the trees are same....\n");
	else
		printf("\nTrees are not same\n");

	int count = 0 ;

	kthSmallestElement(root2 , 5 , &count) ;

	int arr[] = {3,5,8,10,11,13,14,15,22,23,24,25,28,30,35} ;
	struct node *root4 = arrayToBST(arr , 0 , 14) ;

	preorder(root4);

	struct node *del = deleteFromBST(root2 , 15) ;
	preorder(del);


}
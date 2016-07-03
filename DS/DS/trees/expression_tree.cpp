#include<iostream>
#include<stack>
#include<stdio.h>

using namespace std ;

struct node{
	char data ;
	struct node *left , *right ;
} ;

struct node * createNode(char c)
{
	struct node *root = new node ;
	root -> data = c ;
	root -> left = NULL ;
	root -> right = NULL ;
	return root ;
}

struct node *createExpressionTree(string p , int size)
{
	struct node *l , *r , *point ;
	stack <struct node *> S ;
	for (int i = 0; i < size; ++i)
	{
		char t = p[i] ;
		struct node *nd = createNode(t) ;
		if(t != '*' && t != '/' && t != '+' && t != '-')
		{
			S.push(nd) ;
		}
		else
		{
			
			r = S.top() ;
			S.pop() ;
			l = S.top() ;
			S.pop() ;
			nd -> left = l ;
			nd -> right = r ;
			point = nd ;
			S.push(point) ;
		}
	}
	return point ;
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
	string p = "ABC*+D/" ;
	int size = p.size() ;
	struct node *root = createExpressionTree(p , size);
	printf("%c\n", root -> data);
	preorder(root) ;
}
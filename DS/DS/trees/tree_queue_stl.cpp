#include<stdio.h>
#include<malloc.h>
#include<iostream>
#include<queue>
#include<stack>

using namespace std ;

struct node {
	int data ;
	struct node *left , *right ;
};

class nd{
	public :
	int data ;
	nd *left , *right ;
};

int main()
{
	nd *t = new nd ;
	t -> data = 20 ;
	t -> left = NULL ;
	t -> right = NULL ;
	struct node *test = (struct node *)malloc(sizeof(struct node)) ;
	test -> data = 15 ;
	test -> left = NULL ;
	test -> right = NULL ;



	queue <struct node *> Q ;
	queue <nd *> Q2 ;
	stack <struct node *> S ;

	Q.push(test) ;
	Q2.push(t) ;
	S.push(test) ;

	struct node *ret = Q.front() ;
	printf(" %d\n", ret -> data);
	Q.pop() ;
	if(!Q.empty())
		printf("Queue is full\n");
	else
		printf("Queue is empty\n");

	ret = S.top() ;
	S.pop() ;
	if(!S.empty())
		printf("Stack is full\n");
	else
		printf("Stack is empty\n");

	nd *ret2 = Q2.front() ;
	printf(" %d\n", ret2 -> data);
	Q2.pop() ;
	if(!Q2.empty())
		printf("Queue 2 is full\n");
	else
		printf("Queue 2 is empty\n");


}
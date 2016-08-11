#include<stdio.h>

void makeSet(int *S , int size)
{
	int i ;
	for(i = 0 ; i < size ; i++)
		S[i] = -1 ;
}

int find(int *S , int size , int x)
{
	if(x < 0 || x >= size)
		return -1 ;
	if(S[x] <= -1)
		return x ;
	find(S , size , S[x]) ;
}

void Union(int *S , int root1 , int root2 , int size)
{
	if(find(S , size , root1) == find(S , size , root2) && find(S , size , root1) != -1)
		return ;
	if((root1 < 0 || root1 > size)&&(root2 < 0 || root2 > size))
		return ;
	if(S[root2] <= S[root1])
	{
		S[root2] += S[root1] ;
		S[root1] = root2 ;
	}
	else
	{
		S[root1] += S[root2] ;
		S[root2] = root1 ;
	}
}

void display(int *S , int size)
{
	int i ;
	for(i = 0 ; i < size ; i++)
	{
		printf(" %d ", S[i]);
	}
}

int main()
{
	int S[8] ;
	makeSet(S , 8) ;
	Union(S , 5,6 , 8) ;
	Union(S , 1 , 2 , 8) ;
	Union(S , 0 , 2 , 8) ;
	Union(S , 2 , 3 , 8) ;
	display(S , 8) ;

	int p = find(S , 8 , 0);
	printf("%d is the parent of 0\n", p);
}
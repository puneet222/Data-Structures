#include<stdio.h>

int CountTree(int n)
{
	if(n <= 1)
		return 1 ;
	int sum = 0 ;
	int root , left , right ;
	for(root = 1 ; root <= n ; root++)
	{
		left = CountTree(root - 1) ;
		right = CountTree(n - root) ;
		sum = sum + left*right ;
	}
	return sum ;
}

int main()
{
	int n = CountTree(9) ;
	printf("%d is the number of trees\n", n );
}
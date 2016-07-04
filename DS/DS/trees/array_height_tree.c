#include<stdio.h>

int getHieght(int *arr , int n)
{
	int i , j , current_h , max_h = 0;
	for(i = 0 ; i < n ; i++)
	{
		current_h = 0 ;
		j = i ;
		while(arr[j] != -1)
		{
			j = arr[j] ;
			current_h++ ;
		}
		if(current_h > max_h)
			max_h = current_h ;
	}
	return max_h ;
}

int main()
{
	int arr[] = {-1,0,1,6,6,0,0,2,7} ;
	int h = getHieght(arr , 9) ;
	printf("%d\n",h );
}
#include<iostream>
#include<deque>
#include<stdio.h>

using namespace std ;

void getMaxSumWindow(int *arr , int n , int w , int *brr)
{
	int i ;
	deque<int> Q ;
	for(i = 0 ; i < w ; i++)
	{
		while(!Q.empty() && arr[i] > arr[Q.back()])
			Q.pop_back() ;
		Q.push_back(i) ;
	}
	// while(!Q.empty())
	// {
	// 	int a = Q.back() ;
	// 	printf(" %d ", a);
	// 	Q.pop_back() ;
	// }
	for(i = w ; i < n ; i++)
	{
		brr[i-w] = arr[Q.front()] ;
		while(!Q.empty() && arr[i] > arr[Q.back()])
			Q.pop_back() ;
		while(!Q.empty() && Q.front() <= i-w)
			Q.pop_front() ;
		Q.push_back(i) ;
	}
	brr[n-w] = Q.front() ;
}

int main()
{
	int arr[] = {1,3,-1,-3,5,3,6,7} ;
	int n = 8 , w = 3 ;
	int brr[6] ;
	getMaxSumWindow(arr , n , w , brr) ;
	for(int i = 0 ; i < 6 ; i++)
	{
		printf(" %d ", brr[i]);
	}
}
#include<stdio.h>
#include<malloc.h>

struct heap
{
	int *array ;
	int capacity ;
	int count ;
	int heap_type ;
};

struct heap *createHeap(int size , int type)
{
	// type 1 for max heap and 0 for min heap
	struct heap *h = malloc(sizeof(struct heap)) ;
	h -> capacity = size ;
	h -> count = 0 ;
	h -> heap_type = type ;
	h -> array = malloc(h -> capacity * sizeof(int)) ;
	return h ;
}

int leftChild(struct heap *h , int i)
{
	if(h -> count == 0)
		return -1 ;
	if(h -> count < i)
		return -1 ;
	if((2*i+1) > h -> count)
		return -1 ;
	return 2*i+1 ;
}

int rightChild(struct heap *h , int i)
{
	if(h -> count == 0)
		return -1 ;
	if(h -> count < i)
		return -1 ;
	if((2*i+2) > h -> count)
		return -1 ;
	return 2*i+2 ;
}

void resizeHeap(struct heap *h)
{
	h -> capacity *= 2 ;
	h -> array = realloc(h -> array , h -> capacity * sizeof(int)) ;
}

void percolateDown(struct heap *h , int i)
{
	int l , r , max , min; 
	max = i ;
	min = i ;
	l = leftChild(h,i) ;
	r = rightChild(h,i) ;
	if(h -> heap_type == 1)
	{
		if(l > h -> count - 1 || r > h -> count - 1)
		return ;
		if(l != -1 && h -> array[l] > h -> array[i])
			max = l ;
		if(r != -1 && h -> array[r] > h -> array[max])
			max = r ;
		if(max != i)
		{
			int temp = h -> array[i] ;
			h -> array[i] = h -> array[max] ;
			h -> array[max] = temp ;
		}
		else
			return ;
		percolateDown(h , max) ;
	}
	else
	{
		if(l != -1 && h -> array[l] < h -> array[i])
			min = l ;
		if(r != -1 && h -> array[r] < h -> array[min])
			min = r ;
		if(min != i)
		{
			int temp = h -> array[i] ;
			h -> array[i] = h -> array[min] ;
			h -> array[min] = temp ;
		}
		else
			return ;
		percolateDown(h , min) ;
	}
} 

void buildHeap(struct heap *h , int *arr , int n)
{
	if(h -> capacity < n)
	{
		resizeHeap(h) ;
	}
	h -> count = n ;
	int i ,j ;
	for(i = 0 ;  i < n ; i++)
	{
		h -> array[i] = arr[i] ;
	}
	for(i = (n-2)/2 ; i >= 0 ; i--)
	{
		percolateDown(h,i) ;
	}
}

int getNumberOfElements(struct heap *h)
{
	return h -> count ;
}

int deleteMax(struct heap *h)
{
	if(h -> count == 0)
		return -1 ;
	int data = h -> array[0] ;
	h -> array[0] = h -> array[h -> count - 1] ;
	h -> count-- ;
	percolateDown(h , 0) ;
	return data ;
}

int deleteAtIndex(struct heap *h , int i)
{
	if(i < 0 || i > h -> count - 1)
		return -1 ;
	int data = h -> array[i] ;
	h -> array[i] = h -> array[h -> count-1] ;
	h -> count-- ;
	percolateDown(h , i) ;
	return data ;
}

int getMax(struct heap *h)
{
	if(h -> count == 0)
		return -1 ;
	if(h -> heap_type == 1)
	{
		return h -> array[0] ;
	}
	else
	{
		int i , max = -1;
		for(i = (h -> count-1)/2 ; i < h -> count ; i++)
		{
			if(h -> array[i] > max)
				max = h -> array[i] ;
		}
		return max ;
	}
}

void percolateUp(struct heap *h , int i)
{
	// printf("value of i is : %d\n", i);
	int p = (i - 1)/2 ;
	// printf("%d is the parent if %d\n",h -> array[p] , h -> array[i] );
	if(h -> array[p] < h -> array[i])
	{
		int temp = h -> array[p] ;
		h -> array[p] = h -> array[i] ;
		h -> array[i] = temp ;
	}
	else
		return ;
	percolateUp(h , p) ;
}

void insert(struct heap *h , int data)
{
	if(h -> count + 1 > h -> capacity)
	{
		resizeHeap(h) ;
	}
	h -> array[h -> count] = data ;
	h -> count++ ;
	percolateUp(h , h -> count-1) ;
}

void printHeap(struct heap *h)
{
	int i ;
	for(i = 0 ; i < h -> count ; i++)
	{
		printf(" %d ", h -> array[i]);
	}
}

void heapSort(int *arr , int n)
{
	struct heap * h = createHeap(n , 1) ;
	int old_size , temp , i ;
	buildHeap(h , arr , n) ;
	old_size = h -> count ;
	for(i = n-1 ; i > 0 ; i--)
	{
		temp = h -> array[0] ;
		h -> array[0] = h -> array[h -> count - 1] ;
		h -> array[h -> count - 1] = temp ;
		h -> count-- ;
		percolateDown(h , 0) ;
	}
	h -> count = old_size ;
	printHeap(h) ;
}


int main()
{
	int arr[] = {1,2,3,4,5,6,7} ;
	int n = 7 ;
	struct heap *h = createHeap(8 , 1) ;
	buildHeap(h , arr , 7) ;
	int i ;
	int data = deleteMax(h) ;
	printf("%d is the deleted element\n", data);

	
	insert(h , 8);
	insert(h , 10);
	insert(h , 9);
	int c = getNumberOfElements(h) ;
	printHeap(h) ;
	printf("\n");
	printf("Sorting\n");

	int arr2[] = {9,8,7,6,5,4,3,2,1} ;
	heapSort(arr2 , 9) ;
	printf("\n\n\nmin heap\n");  /*------------------------------- MIN   HEAP -----------------------------*/
	int arr3[] = {7,5,1,7,9,12,10} ;
	int n2 = 7 ;
	struct heap *h2 = createHeap(n2,0) ;
	buildHeap(h2 , arr3 , n2) ;
	for(i = 0 ; i < n2 ; i++)
	{
		printf(" %d ", h2 -> array[i]);
	}
	int maxin = getMax(h2);
	printf("maximum element in the min heap is : %d\n", maxin);
	int k = deleteAtIndex(h2 , 1);
	printf("deleted element is %d\n", k);
	printHeap(h2) ;
}

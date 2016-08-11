#include<stdio.h>
#include<malloc.h>

// it is queue implementation of heap almost same as stack but change in priority of inserting elements in the heap
// insert function is used as push and delete function is used as pop

struct data
{
	int dat ;
	int priority ;
};

struct heap
{
	struct data *array ;
	int capacity ;
	int count ;
	int heap_type ;
};

void resizeHeap(struct heap *h)
{
	h -> capacity *= 2 ;
	h -> array = realloc(h -> array , h -> capacity*(sizeof(struct data))) ;
}

struct heap *createHeap(int size , int type)
{
	struct heap *h = malloc(sizeof(struct heap)) ;
	h -> capacity = size ;
	h -> heap_type = type ;
	h -> array = malloc(h -> capacity * sizeof(struct data)) ;
	return h ;
}


int leftChild(struct heap *h , int i)
{
	if(i > h -> count - 1)
		return -1 ;
	if(2*i + 1 > h -> count - 1)
		return -1 ;
	return 2*i + 1 ;
}

int rightChild(struct heap *h , int i)
{
	if(i > h -> count - 1)
		return -1 ;
	if(2*i + 2 > h -> count - 1)
		return -1 ;
	return 2*i + 2 ;
}

void percolateDown(struct heap *h , int i)
{
	int p = (i-1)/2 ;
	int l , r , min = i ;
	l = leftChild(h,i) ;
	r = rightChild(h , i) ;
	if(l != -1 && h -> array[l].priority < h -> array[i].priority)
		min = l ;
	if(r != -1 && h -> array[r].priority < h -> array[min].priority)
		min = r ;
	if(min != i)
	{
		struct data temp = h -> array[i] ;
		h -> array[i] = h -> array[min] ;
		h -> array[min] = temp ;
	}
	else
		return  ;
	percolateDown(h , min) ;

}

void percolateUp(struct heap *h , int i)
{
	if(i == 0)
		return ;
	int p = (i-1)/2 ;
	// printf("%d is the parent priority and %d is the passes priority\n", h -> array[p].priority , h -> array[i].priority );
	if(h -> array[i].priority < h -> array[p].priority)
	{
		// printf("in if statement\n");
		struct data temp = h -> array[i] ;
		h -> array[i] = h -> array[p] ;
		h -> array[p] = temp ;
	}
	else
		return ;
	percolateUp(h , p) ;
}

void insert(struct heap *h , int data , int priority)
{
	if(h -> count == h -> capacity)
	{
		resizeHeap(h) ;
		printf("resizing...\n");
		// printf("heap full\n");
		// return ;
	}
	(h -> array[h -> count]).dat = data ;
	(h -> array[h -> count]).priority = priority ;
	h -> count++ ;
	percolateUp(h , h -> count - 1) ;
}

int delete(struct heap *h)
{
	if(h -> count == 0)
	{
		printf("No element in the heap\n");
		return ;
	}
	int data = h -> array[0].dat ;
	h -> array[0] = h -> array[h -> count -1] ;
	h -> count-- ;
	percolateDown(h , 0) ;
	return data ;
}

void displayHeap(struct heap *h)
{
	int i ;
	for(i = 0 ; i < h -> count ; i++)
	{
		printf(" %d ", (h -> array[i]).dat);
	}
}

int main()
{
	struct heap *h = createHeap(2 , 0) ;
	// we need a variable which we use as priority so c will be our priority variable
	int c = 0 ;
	int i , n;
	for(i = 0 ; i < 8 ; i++)
	{
		printf("Enter the element you want enter to queue\n");
		scanf("%d" , &n) ;
		insert(h , n , c) ;
		c++ ;
	}
	displayHeap(h);
	int key = delete(h) ;
	printf("\n\n%d is the deleted element \n", key);
	delete(h);
	displayHeap(h);
}
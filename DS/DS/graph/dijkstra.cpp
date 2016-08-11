#include<iostream>
#include<malloc.h>
#include<queue>
#include<stdio.h>

using namespace std ;

struct heap
{
	int capacity ;
	int count ;
	int *array ;
	int *priority ;
};

struct heap *createHeap(int size)
{
	struct heap *h = new heap ;
	h -> capacity = size ;
	h -> count = 0 ;
	h -> array = (int *)malloc(sizeof(int)*h -> capacity) ;
	h -> priority = (int *)malloc(sizeof(int)*h -> capacity) ;
	return h ;
}

void resizeHeap(struct heap *h)
{
	h -> capacity *= 2 ;
	h -> array = (int *)realloc(h -> array , h -> capacity) ;
	h -> priority = (int *)realloc(h -> priority , h -> capacity) ;
}

void percolateUp(struct heap *h , int i)
{
	int p = (i - 1)/2 ;
	if(h -> priority[p] > h -> priority[i])
	{
		int pritemp = h -> priority[i] ;
		int dtemp = h -> array[i] ;
		h -> priority[i] = h -> priority[p] ;
		h -> array[i] = h -> array[p] ;
		h -> priority[p] = pritemp ;
		h -> array[p] = dtemp ;
	}
	else{
		return ;
	}
	percolateUp(h , p) ;
}

void insert(struct heap *h , int data , int priority)
{
	if(h -> count == h -> capacity - 1)
		resizeHeap(h) ;
	if(h -> count == 0)
	{
		h -> array[h -> count] = data ;
		h -> priority[h -> count] = priority;
		h -> count++ ;
		return ;
	}
	h -> array[h -> count] = data ;
	h -> priority[h -> count] = priority ;
	h -> count++ ;
	percolateUp(h , h -> count - 1) ;
}

int isEmpty(struct heap *h)
{
	return (h -> count == 0) ;
}

void printHeap(struct heap *h)
{
	for (int i = 0; i < h -> count; ++i)
	{
		printf("%d is the data &&&& %d is the priority\n", h -> array[i] , h -> priority[i]);
	}
}

int leftChild(struct heap *h , int i)
{
	if(i >= h -> count)
		return -1 ;
	if(2*i+1 >= h -> count)
		return -1 ;
	return 2 * i + 1 ;
}

int rightChild(struct heap *h , int i)
{
	if(i >= h -> count)
		return -1 ;
	if(2*i+2 >= h -> count)
		return -1 ;
	return 2 * i + 2 ;
}

void percolateDown(struct heap *h , int i)
{
	int l , r , min = i ;
	l = leftChild(h , i) ;
	r = rightChild(h , i) ;
	// cout << r << " is the right child\n" ;
	// cout << l << " is the left child\n" ;
	if(l != -1 && h -> priority[l] < h -> priority[min])
		min = l ;
	if(r != -1 && h -> priority[r] < h -> priority[min])
		min = r ;
	if(min != i)
	{
		int pritemp = h -> priority[i] ;
		int dtemp = h -> array[i] ;
		h -> priority[i] = h -> priority[min] ;
		h -> array[i] = h -> array[min] ;
		h -> priority[min] = pritemp ;
		h -> array[min] = dtemp ;
	}
	else
	{
		return ;
	}
	percolateDown(h , min) ;
}

int* deleteMin(struct heap *h)
{
	if(h -> count == 0)
		return NULL;
	static int r[2] ;
	r[0] = h -> array[0] ;
	r[1] = h -> priority[0] ;
	h -> array[0] = h -> array[h -> count - 1] ;
	h -> priority[0] = h -> priority[h -> count - 1] ;
	percolateDown(h , 0) ;
	h -> count-- ;
	return r ;
}

int getSearchIndex(struct heap *h , int data)
{
	for (int i = 0; i < h -> count; ++i)
	{
		if(h -> array[i] == data)
			return i ;
	}
}

void update(struct heap *h , int data , int dist)
{
	int index = getSearchIndex(h , data) ;
	h -> priority[index] = dist ;
	percolateDown(h , 0) ;
}

struct graph{
	int e ;
	int v ;
	int **wgh ;
} ;

struct graph *weightMatrix(int vertices , int edges)
{
	struct graph *g = new graph ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> wgh = (int **)malloc(sizeof(int *)*(g -> v)) ;
	for (int i = 0; i < g -> v; ++i)
	{
		g -> wgh[i] = (int *)malloc(sizeof(int)*(g -> v)) ;
	}
	int u , v ;
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			g -> wgh[u][v] = 0 ;
		}
	}

	for (int i = 0; i < g -> e; ++i)
	{
		printf("Enter the vertices u and v such that there is an edge u -> v is there : ");
		cin >> u >> v ;
		int w ;
		cout << "\nEnter the weight of the edge : " ;
		cin >> w ;
		g -> wgh[u][v] = w ;
	}
	return g ;
}

void printGraph(struct graph *g)
{
	int u , v ;
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			printf(" %d ", g -> wgh[u][v]);
		}
		printf("\n");
	}
}

void shortestPath(struct graph *g , int s , int *distance , int *path)
{
	for (int i = 0; i < g -> v; ++i)
	{
		distance[i] = -1 ;
	}
	distance[s] = 0 ;
	path[s] = -1 ;
	struct heap *h = createHeap(2) ;
	insert(h , s , 0) ;
	while(!isEmpty(h))
	{
		int *r = deleteMin(h) ;
		int v = r[0] ;
		int d = r[1] ;
		for (int i = 0; i < g -> v; ++i)
		{
			if(g -> wgh[v][i])
			{
				int dnew = distance[v] + g -> wgh[v][i] ;
				if(distance[i] == -1)
				{
					distance[i] = dnew ;
					insert(h , i , dnew) ;
					path[i] = v ;
				}
				if(distance[i] > dnew)
				{
					distance[i] = dnew ;
					update(h , i , dnew) ;
					path[i] = v ;
				}
			}
		}
	}
}

int main()
{
	int v , e ;
	cout << "Enter number of vertices and number of edges in the graph : " ;
	cin >> v >> e ;
	struct graph *g = weightMatrix(v ,e) ;
	printGraph(g) ;
	int distance[g -> v] ;
	int path[g -> v] ;
	int s ;
	printf("Enter the source from where you want shortest path to all other nodes : ");
	cin >> s ;
	shortestPath(g  , s , distance , path);
	for (int i = 0; i < g -> v; ++i)
	{
		printf(" %d ", distance[i]);
	}
	// struct heap *h = createHeap(2) ;
	// insert(h , 5 , 1) ;
	// insert(h , 10 , 3) ;
	// insert(h , 15 , 5) ;
	// insert(h , 50 , 4) ;
	// insert(h , 25 , 2) ;
	// printHeap(h) ;
	// int *r = deleteMin(h) ;
	// printf("%d is the deleted element" , r[1]) ;
	// printHeap(h) ;
	// update(h , 15 , 1) ;
	// printHeap(h) ;
}
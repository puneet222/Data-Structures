#include<stdio.h>
#include<malloc.h>

struct node{
	int vertexNumber ;
	struct node *next ;
} ;

struct graph{
	int v ;
	int e ;
	struct node **adj ;
} ;

struct graph *adjacencyList(int vertices , int edges)
{
	struct graph *g = malloc(sizeof(struct graph)) ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> adj = malloc(sizeof(struct node)*g -> v) ;
	
	// g -> adj[0] = temp ;
	// printf("%d\n", g -> adj[0] -> vertexNumber);
	int i ; 
	for(i = 0 ; i < g -> v ; i++)
	{
		g -> adj[i] = malloc(sizeof(struct node)) ;
		g -> adj[i] -> vertexNumber = i ;
		g -> adj[i] -> next = NULL ;
	}
	// printf("%d" , g -> adj[2] -> vertexNumber) ;
	for(i = 0 ; i < g -> e ; i++)
	{
		int u , v ;
		printf("Enter the vertices having an edge between them : ");
		scanf("%d%d" , &u , &v) ;
		struct node *temp = malloc(sizeof(struct node)) ;
		temp -> vertexNumber = v ;
		temp -> next = NULL ;
		struct node *ptr = g -> adj[u] ;
		while(ptr -> next != NULL)
		{
			ptr = ptr -> next ;
		}
		ptr -> next = temp ;

		struct node *temp2 = malloc(sizeof(struct node)) ;
		temp2 -> vertexNumber = u ;
		temp2 -> next = NULL ;
		ptr = g -> adj[v] ;
		while(ptr -> next != NULL)
		{
			ptr = ptr -> next ;
		}
		ptr -> next = temp2 ;
	}
	return g ;
}

void printGraph(struct graph *g)
{
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		printf("%d is the vertex\n" , i) ;
		struct node *ptr ;
		ptr = g -> adj[i] ;
		while(ptr  != NULL)
		{
			printf(" %d ", ptr -> vertexNumber);
			ptr = ptr -> next ;
		}
		printf("\n") ;
	}
}

int main()
{
	int e , v ;
	printf("Enter number of vertices and number of edges : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyList(v,e) ;
	// printf("%d\n", g -> adj[2] -> next -> next -> vertexNumber);
	printGraph(g) ;
}
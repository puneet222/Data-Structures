#include<stdio.h>
#include<malloc.h>

struct graph{
	int v ;
	int e ;
	int **adj ;
} ;

struct graph *adjacencyMatrix(int vertices , int edges)
{
	struct graph *g = malloc(sizeof(struct graph)) ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> adj = malloc(sizeof(int * )*(g -> v)) ;
	int i ;
	for (i = 0; i < g -> v; ++i)
    	g -> adj[i] = malloc((g -> v) * sizeof(int));

	if(!g -> adj)
		printf("Cannot create a empty matrix\n");
	int u , v , j ;
	// g->adj[0][0] = 5 ;
	// g->adj[0][1] = 5 ;
	// g->adj[0][2] = 5 ;
	printf("%d is the no. of vertices and %d is the no. of edges\n", g -> v , g -> e);
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			g -> adj[u][v] = 0 ;
		}
	}
	for(i = 0 ; i < g -> e ; i++)
	{
		printf("Enter the vertices having an edge : ");
		scanf("%d%d" , &u,&v) ;
		g -> adj[u][v] = 1 ;
		g -> adj[v][u] = 1 ;
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
			printf(" %d ", g -> adj[u][v]);
		}
		printf("\n");
	}
}

void printVisit(struct graph *g , int *visited)
{
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		printf(" %d ", visited[i]);
	}
	printf("\n");
}


int totalSimplePath(struct graph * g  , int s , int d , int *visited)
{
	int t ;
	int count = 0 ;
	visited[s] =  1;
	if(s == d)
	{
		visited[s] = 0 ;
		return 1;
	}
	for(t = 0 ; t < g -> v ; t++)
	{
		if(!visited[t] && g -> adj[s][t])
			{
				count += totalSimplePath(g , t , d , visited) ;
				visited[t] = 0 ;
			}
	}
	return count ;
}


int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g);
	int visited[g -> v] ;
	int i ;
	for(i = 0  ; i < g -> v ; i++)
	{
		visited[i] = 0 ;
	}

	int s , d ;
	printf("Enter the source and destination of which you want to find the simple path : ");
	scanf("%d%d" , &s , &d) ;
	int count = 0 ;
	count = totalSimplePath(g , s , d , visited) ;
	printf("Total simple path from %d to %d is %d \n", s , d , count);
}
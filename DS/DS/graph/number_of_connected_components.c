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

void dfs(struct graph *g , int u , int *visited)
{
	int i ;
	visited[u] = 1 ;
	for(i = 0 ; i < g -> v ; i++)
	{
		if(!visited[i] && g -> adj[u][i])
			dfs(g , i , visited) ;
	}
}

int connectedComponent(struct graph *g)
{
	int count = 0 ;
	int visited[g -> v] ;
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		visited[i] = 0 ;
	}
	for(i = 0 ; i < g -> v ; i++)
	{
		if(!visited[i])
		{
			dfs(g , i , visited) ; 
			count++ ;
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
	int c = connectedComponent(g) ;
	printf("%d is the connectedComponent of the graph\n", c);
}
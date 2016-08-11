#include<stdio.h>
#include<malloc.h>

struct graph
{
	int v ;
	int e ;
	int **adj ;
};

struct graph *adjacencyMatrix(int vertices , int edges)
{
	struct graph *g = malloc(sizeof(struct graph)) ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> adj = malloc(sizeof(int * )*(g -> v)) ;
	int i ;
	for (i = 0; i < g -> v; ++i)
    	g -> adj[i] = malloc((g -> v) * sizeof(int));
    int u , v ;
    for(u = 0 ; u < g -> v ; u++)
    {
    	for(v = 0 ; v < g -> v ; v++)
    	{
    		g -> adj[u][v] = 0 ;
    	}
    }

    for(i= 0 ; i < g -> e ; i++)
    {
    	printf("Enter the nodes having an edge between them : ");
    	scanf("%d%d" , &u , &v) ;
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
			printf(" %d " , g -> adj[u][v]) ;
		}
		printf("\n");
	}
}

void dfs(struct graph *g , int *visited , int u)
{

		visited[u] = 1 ;
		printf("\n------- Visited node %d ------------\n"  , u);
		int j ;
		for(j = 0 ; j < g -> v ; j++)
		{
			if(!visited[j] && g -> adj[u][j])
			{
				dfs(g , visited , j) ;
			}
		}

}

void beginTraversal(struct graph *g)
{
	int visited[g -> v] ;
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		visited[i] = 0 ;
	}
	int s = g -> v ;
	for(i = 0 ; i  < g -> v ; i++)
		printf(" %d " , visited[i]) ;
	dfs(g , visited , 0) ;
	printf("\n");
	for(i = 0 ; i  < g -> v ; i++)
		printf(" %d " , visited[i]) ;
}

int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g) ;
	int i ;
	beginTraversal(g) ;
}


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

int checkIndegree(struct graph *g , int s)
{
	int i ;
	for( i = 0 ; i < g -> v ; i++)
	{
		if(g -> adj[i][s])
			return 1 ;
	}
		return 0 ;
}

int checkOutdegree(struct graph *g , int s)
{
	int i ;
	for( i = 0 ; i < g -> v ; i++)
	{
		if(g -> adj[s][i])
			return 1 ;
	}
		return 0 ;
}

void delete(struct graph *g , int s)
{
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		g -> adj[s][i] = 0 ;
		g -> adj[i][s] = 0 ;
	}
}




int hasCycle(struct graph *g , int s , int *cycle)
{
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		printf("value if i is %d\n", i);
		if(!checkOutdegree(g , i))
		{
			delete(g , i) ;
			cycle[i] = 0 ;
		}
		else
		{
			if(!checkIndegree(g , i))
			{
				delete(g , i) ;
				cycle[i] = 0 ;
			}
		}
	}
	printf("Printing cycle\n");
	for(i = 0 ; i < g -> v ; i++)
	{
		printf(" %d ", cycle[i]);
	}

	for(i = 0 ; i < g -> v ; i++)
	{
		if(!checkOutdegree(g , i) && cycle[i])
			hasCycle(g , s , cycle) ;
		if(!checkIndegree(g , i) && cycle[i])
			hasCycle(g , s , cycle) ;
	}
	for(i = 0 ; i < g -> v ; i++)
	{
		if(cycle[i] == 1)
			return 1 ;
	}
		return 0 ;
}

int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g);
	int cycle[g -> v] ;
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		cycle[i] = 1 ;
	}
	if(hasCycle(g, 0 , cycle))
		printf("has Cycle\n");
	else
		printf("no cycle\n");
}
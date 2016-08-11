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

void printParentArray(struct graph *g , int *parent)
{
	printf("\n");
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		printf(" %d ", parent[i]);
	}
}

int hasCycle(struct graph *g , int s , int *parent , int *visited)
{
	int hascycle = 0 ;
	int flag = 0 ;
	int v ;
	visited[s] = 1 ;
	for(v = 0 ; v < g -> v ; v++)
	{
		if(g -> adj[s][v])
		{
			// node is adjacent
			if(!visited[v])
			{
				// not visited that node
				parent[v] = s ;
				if(hasCycle(g , v , parent , visited))
					return 1 ;
			}
			else
			{
				if(parent[s] == v)
				{
					// no cycle till now
				}
				else
				{
					printf("\n---------v1 = %d and --- v2 = %d  and the value of parent is %d\n", s , v , parent[s]);
					printf("\n\n--------------------------------In else has cycle true\n");
					hascycle = 1 ;
				}
			}
		}
	}
	return hascycle ;
}

int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g);
	int parent[g -> v] ;
	int visited[g -> v] ;
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		parent[i] = 0 ;
		visited[i] = 0 ;
	}

	int r = hasCycle(g , 0 , parent , visited) ;
	printf("%d is the value returned by function\n", r);
		for(i = 0 ; i < g -> v ; i++)
	{
		parent[i] = 0 ;
		visited[i] = 0 ;
	}

	if(hasCycle(g , 0 , parent , visited) == 1)
		printf("has cycle\n");
	else
		printf("No cycle\n");
}
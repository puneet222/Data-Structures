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

int sink(struct graph *g)
{
	int a = 0 , i;
	for(i = 1 ; i < g -> v ; i++)
	{
		if(g -> adj[a][i])
			a = i ;
	}

	// so a contains the node having all the edges inserted into it if(a != last vertex) because otherwise we have to check an outgoing edge from a ;
	// now first we check whether the in edges are from all nodes or not ;
	int count = 0 ;
	for(i = 0 ; i < g -> v ; i++)
	{
		if(i == a)
			continue ;
		if(g -> adj[i][a])
			count++ ;
	}
	printf("value of count is %d\n", count);
	if(count == g -> v - 1) // because except that vertex
	{
		// then a might be sink but we have to check whether it is the last node or not
		if(a == g -> v - 1)
		{
			// last node
			for(i = 0 ; i < g -> v ; i++)
			{
				if(g -> adj[a][i])
					return -1 ;
			}
		}
		else
			return a ;
	}
	else
		return -1 ;
}

int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g);
	int s = sink(g) ;
	if(s == -1)
		printf("Not sink in the graph\n");
	else
		printf("there exist a universal in the graph %d\n", s);
}
#include<iostream>
#include<queue>
#include<limits.h>
#include<stdio.h>
#include<malloc.h>

using namespace std ;

struct graph{
	int v ;
	int e ;
	int **adj ;
	int *indegree ;
} ;

struct graph *adjacencyMatrix(int vertices , int edges)
{
	struct graph *g = new graph ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> adj = (int **)malloc(sizeof(int * )*(g -> v)) ;
	int i ;
	for (i = 0; i < g -> v; ++i)
    	g -> adj[i] = (int *)malloc((g -> v) * sizeof(int));

	if(!g -> adj)
		printf("Cannot create a empty matrix\n");
	g -> indegree = (int *)malloc(sizeof(int)*(g -> v)) ;
	int u , v , j ;
	printf("%d is the no. of vertices and %d is the no. of edges\n", g -> v , g -> e);
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			g -> adj[u][v] = 0 ;
		}
		g -> indegree[i] = 0 ;
	}
	for(i = 0 ; i < g -> e ; i++)
	{
		printf("Enter the vertices having an edge : ");
		scanf("%d%d" , &u,&v) ;
		g -> adj[u][v] = 1 ;
		g -> indegree[v]++ ;
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

int depth(struct graph *g)
{
	int count = 0 ;
	queue <int> Q ;
	int s ;
	for (int i = 0; i < g -> v; ++i)
	{
		if(g -> indegree[i] == 0)
		{
			Q.push(i) ;
		}
	}
	Q.push(INT_MAX) ;
	while(!Q.empty())
	{
		int u = Q.front() ;
		Q.pop() ;
		if(u == INT_MAX)
		{
			count++ ;
			// another level
			if(!Q.empty())
				Q.push(INT_MAX) ;
		}
		else
		{
			for (int i = 0; i < g -> v; ++i)
			{
				if(g -> adj[u][i])
				{
					g -> indegree[i]-- ;
					if(g -> indegree[i] == 0)
						Q.push(i) ;
				}
			}
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
	int i ;
	printf("indegree\n");
	for(i = 0 ; i < g -> v ; i++)
	{
		printf(" %d " , g -> indegree[i]);
	}
	int count = depth(g) ;
	printf("Depth of the graph is : %d\n", count);
}
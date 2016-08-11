#include<iostream>
#include<malloc.h>
#include<queue>
#include<stdio.h>

using namespace std ;

struct graph{
	int v ;
	int e ;
	int **adj ;
} ;

struct graph *adjacencyMatrix(int vertices , int edges)
{
	struct graph *g = new graph ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> adj = (int **)malloc(sizeof(int *)*(g -> v)) ;
	for (int i = 0; i < g -> v; ++i)
	{
		g -> adj[i] = (int *)malloc(sizeof(int)*(g -> v)) ;
	}
	int u , v ;
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			g -> adj[u][v] = 0 ;
		}
	}

	for (int i = 0; i < g -> e; ++i)
	{
		printf("Enter vertices u , v having an edge from u to v : ");
		scanf("%d%d" , &u , &v) ;
		g -> adj[u][v] = 1 ;
	}
	return g ;
}

void topologicalSort(struct graph *g)
{
	queue <int> Q ;
	int indegree[g -> v] ;
	int u , v ;
	for(u = 0 ; u < g -> v ; u++)
	{
		int sum = 0 ;
		for(v = 0 ; v < g -> v ; v++)
		{
			sum = sum + g -> adj[v][u] ;
		}
		indegree[u] = sum ;
	}
	// printf("\n Indegree \n");
	// for (int i = 0; i < g -> v; ++i)
	// {
	// 	printf(" %d ", indegree[i]);
	// }
	int count = 0 ;
	for(int i = 0 ; i < g -> v ; i++)
	{
		if(indegree[i] == 0)
			Q.push(i) ;
	}
	while(!Q.empty())
	{
		u = Q.front() ;
		count++ ;
		printf(" %d ", u);
		Q.pop() ;
		for(v = 0 ; v < g -> v ; v++)
		{
			if(g -> adj[u][v])
			{
				indegree[v]-- ;
				if(indegree[v] == 0)
					Q.push(v) ;
			}
		}
	}
	if(count != g -> v)
		printf("\nGraph has cycle\n");
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

int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g);
	topologicalSort(g) ;
}
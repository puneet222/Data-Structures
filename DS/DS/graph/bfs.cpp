#include<iostream>
#include<stdio.h>
#include<malloc.h>
#include<queue>

using namespace std ;

struct graph
{
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
	int i ;
	for(i = 0 ; i < g -> v ; i++)
	{
		g -> adj[i] = (int *)malloc((g -> v) * sizeof(int)) ;
	}
	int u,v ;
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			g -> adj[u][v] = 0 ;
		}
	}

	for(i = 0 ; i < g -> e ; i++)
	{
		printf("Enter the nodes having an edge between them : ");
		scanf("%d%d" , &u , &v) ;
		g -> adj[u][v] = 1 ;
		g -> adj[v][u] = 1 ;
	}

	return g ;
}

void bfs(struct graph *g , int u , int *visited)
{
	queue <int> Q ;
	Q.push(u) ;
	
	int j = 0 ;
	while(!Q.empty())
	{
		j++ ;
		int p = Q.front() ;
		printf("\n------------Visited Node %d------------\n", p);
		Q.pop() ;
		visited[p] = 2 ;
		int i ;
		for(i = 0 ; i < g -> v ; i++)
		{
			if(visited[i] != 2 && g -> adj[p][i])
			{
				if(visited[i] != 1)
				{
					Q.push(i) ;
					visited[i] = 1 ;
				}
			}
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
	bfs(g , 0 , visited) ;
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
	beginTraversal(g) ;
}
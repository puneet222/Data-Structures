#include<iostream>
#include<malloc.h>
#include<stdio.h>
#include<queue>

using namespace std ;

struct graph
{
	int v ;
	int e ;
	int **adj ;
};

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

	for(int i = 0 ; i < g -> e ; i++)
	{
		printf("Enter the vertices u and v such that there is an edge u -> v is there : ");
		cin >> u >> v ;
		g -> adj[u][v] = 1 ;
	}
	printGraph(g) ;
	return g ;

}

void shortestPath(struct graph *g , int *distance , int *path , int s)
{
	for (int i = 0; i < g -> v; ++i)
	{
		distance[i] = -1 ;
	}
	distance[s] = 0 ;
	queue <int> Q ;
	Q.push(s) ;
	while(!Q.empty())
	{
		int v = Q.front() ;
		Q.pop() ;
		for (int i = 0; i < g -> v; ++i)
		{
			if(g -> adj[v][i])
			{
				if(distance[i] == -1)
				{
					distance[i] = distance[v] + 1 ;
					path[i] = v ;
					Q.push(i) ;
				}
			}
		}
	}
}



int main()
{
	int v , e ;
	printf("Enter number of vertices and edges in the graph : ");
	scanf("%d%d" , &v , &e) ;
	struct graph *g = adjacencyMatrix(v , e) ;
	printGraph(g);
	int distance[g -> v] ;
	int path[g -> v] ;
	int s ;
	printf("Enter the node from where you want find the shortest distance to all nodes\n");
	cin >> s ;
	shortestPath(g , distance , path , s) ;
	for (int i = 0; i < g -> v; ++i)
	{
		printf(" %d ", distance[i]);
	}
}
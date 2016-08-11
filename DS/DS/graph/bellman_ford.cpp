#include<iostream>
#include<stdio.h>
#include<queue>
#include<malloc.h>
#include<limits.h>

using namespace std ;

struct graph{
	int v ;
	int e ;
	int **wgh ;
} ;

struct graph *weightMatrix(int vertices , int edges)
{
	struct graph *g = new graph ;
	g -> v = vertices ;
	g -> e = edges ;
	g -> wgh = (int **)malloc(sizeof(int *)*(g -> v)) ;
	for (int i = 0; i < g -> v; ++i)
	{
		g -> wgh[i] = (int *)malloc(sizeof(int)*(g -> v)) ;
	}
	int u , v ;
	for(u = 0 ; u < g -> v ; u++)
	{
		for(v = 0 ; v < g -> v ; v++)
		{
			g -> wgh[u][v] = 0 ;
		}
	}

	for (int i = 0; i < g -> e; ++i)
	{
		printf("Enter the vertices u and v such that there is an edge u -> v is there : ");
		cin >> u >> v ;
		int w ;
		cout << "\nEnter the weight of the edge : " ;
		cin >> w ;
		g -> wgh[u][v] = w ;
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
			printf(" %d ", g -> wgh[u][v]);
		}
		printf("\n");
	}
}

void shortestpath(struct graph *g , int * distance , int *path , int s)
{
	queue <int> Q ;
	int qarr[g -> v] ;
	for (int i = 0; i < g -> v; ++i)
	{
		distance[i] = INT_MAX ;
		qarr[i] = 0 ;
	}
	distance[s] = 0 ;
	Q.push(s) ;
	qarr[s] = 1 ;
	while(!Q.empty())
	{
		int v = Q.front() ;
		Q.pop() ;
		qarr[v] = 0 ;
		for (int i = 0; i < g -> v; ++i)
		{
			if(g -> wgh[v][i])
			{
				int dnew = distance[v] + g -> wgh[v][i] ;
				if(distance[i] > dnew)
				{
					distance[i] = dnew ;
					path[i] = v ;
					if(qarr[i] == 0)
					{
						Q.push(i) ;
						qarr[i] == 1 ;
					}
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
	struct graph *g = weightMatrix(v , e) ;
	printGraph(g);
	int distance[g -> v] ;
	int path[g -> v] ;
	int s ;
	printf("Enter the source from where you want to find the shortest path to all other nodes : ");
	cin >> s ;
	shortestpath(g , distance , path , s) ;
	for (int i = 0; i < g -> v; ++i)
	{
		printf(" %d ", distance[i]);
	}
}
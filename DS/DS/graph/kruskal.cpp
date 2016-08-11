#include<iostream>
#include<stdio.h>
#include<malloc.h>
#include<algorithm>
#include<vector>

using namespace std ;


struct edgeInfo{
	int v1 ;
	int v2 ;
	int w ;
} ;

struct graph{
	int v ;
	int e ;
	int **wgh ;
} ;

struct graph *weightMatrix(int vertices , int edges , struct edgeInfo *graphInfo)
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
		printf("Enter the vertices u and v such that there is an edge between them : ");
		cin >> u >> v ;
		int w ;
		cout << "\nEnter the weight of the edge : " ;
		cin >> w ;
		g -> wgh[u][v] = w ;
		g -> wgh[v][u] = w ;
		graphInfo[i].v1 = u ;
		graphInfo[i].v2 = v ;
		graphInfo[i].w = w ;
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

void makeSet(int *S , int size)
{
	for (int i = 0; i < size; ++i)
	{
		S[i] = i ;
	}
}

void printSet(int *S , int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf(" %d ", S[i]);
	}
}

bool myfunction(struct edgeInfo a , struct edgeInfo b)
{
	return a.w < b.w ;
}

int Find(int *S , int size , int x)
{
	if(x < 0 || x >= size)
		return -1;
	if(S[x] == x)
		return x ;
	Find(S , size , S[x]) ;
}

void Union(int *S , int size , int u , int v)
{
	if((u < 0 || u >= size) || (u < 0 || u >= size))
		return ;
	if(Find(S , size , u) == Find(S , size , v))
		return ;
	int p = Find(S , size , u) ; 
	S[p] = v ;
}


std::vector<struct edgeInfo> kruskal(struct graph *g , struct edgeInfo *graphInfo)
{
	std::vector<struct edgeInfo> result;
	int S[g -> v] ;
	makeSet(S , g -> v) ;
	printf("\nPrinting set\n");
	printSet(S , g -> v) ;
	printf("\n");
	int u , v ;
	int size = g -> v ;
	sort(graphInfo , graphInfo + g -> e , myfunction) ; // sort the edges of the graph ;
	for (int i = 0; i < g -> e; ++i)
	{
		printSet(S , size) ;
		printf("\n");
		u = graphInfo[i].v1 ;
		v = graphInfo[i].v2 ;
		if(Find(S , size , u) != Find(S , size , v))
		{
			result.push_back(graphInfo[i]);
			Union(S , size , u , v) ;
		}
	}
	return result ;
}

void printGraphStructure(struct graph *g, struct edgeInfo *edge)
{
	for (int i = 0; i < g -> e; ++i)
	{
		printf("%d is vertex 1    %d is vertex 2      %d is the weight\n", edge[i].v1 , edge[i].v2 , edge[i].w);
	}
}

int main()
{
	int v , e ;
	cout << "Enter number of vertices and number of edges in the graph : " ;
	cin >> v >> e ;
	struct edgeInfo graphInfo[e] ;
	struct graph *g = weightMatrix(v ,e , graphInfo) ;
	printGraph(g) ;
	
	std::vector<struct edgeInfo> result =  kruskal(g , graphInfo) ;
	int size = result.size() ;
	printf("%d is the size of vector\n", size);
	for (int i = 0; i < size; ++i)
	{
		printf("%d ------------- %d   (weight = %d)\n", result[i].v1 , result[i].v2 , result[i].w);
	}
	printGraphStructure(g , graphInfo) ;
}
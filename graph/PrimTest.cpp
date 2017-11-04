#include<stdio.h>
#include<stdlib.h>

#define M 20
#define FINITY 5000

typedef char vertexttype;
typedef int edgetype;
typedef struct
{
	vertexttype vexs[M];
	edgetype edges[M][M];
	int n,e;
}Mgraph;

typedef struct edgedata
{
	int beg,en;
	int length;
}edge;

void prim(Mgraph g,edge tree[M-1])
{
	edge x;
	int d,min,j,k,s,v;
	for(v = 1;v < g.n-1;v++)
	{
		tree[v-1].beg=0;
	}
}
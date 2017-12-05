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
		tree[v-1].en = 0;
		tree[v-1].length = g.edges[0][v]; 
	}
	for(k = 0;k < g.n-3;k++)
	{
		min=tree[k].length;
		s = k;
		for(j=k+1;j < g.n-2;j++)
		{
			if(tree[j].length < min)
			{
				min = tree[j].length;
				s = j;
			}
		}
		v = tree[s].en;//入选顶点为v
		
		x = tree[s];
		tree[s] = tree[k];//通过交换，将当前最小边加入TREE中
		for(j = k+1;j < =g.n-2;j++)
		{
			d = g.edges[v][tree[j].en];
			if(d < tree[j].length)
			{
				tree[j].length = d;
				tree[j].beg = v;	
			}	
		} 
	 } 
	 printf("\n最小生成树：\n");
	 for(j = 0;j <= g.n-2;j++)
	 {
	 	printf("\n%c---%c  %d\n",g.vexs[tree[j].beg],g.vexs[tree[j].en],tree[j].length);
	 }
	 printf("\n\nthe root of it is %c\n",g.vexs[0]);
}

















#include<stdio.h>
#include<malloc.h>
#define FINITY 5000
#define M 20

typedef char vertextype;
typedef int edgetype; 
typedef struct
{
	vertextype vex[M];
	edgetype edges[M][M];
	int n,e;
}Mgraph;

typedef struct edgedata //用于保存最小生成树的边类型定义 
{
	int beg,en;//beg,en是边顶点的序号 
	int length;//边的权值长 
}edge;

//创建图 
void create(Mgraph *g,char *s,int c)
{
	int i,j,k,w;
	FILE *rf;
	rf = fopen(s,"r");//从文件中读取图的信息
	if(rf)
	{
		fscanf(rf,"%d%d",&g->n,&g->e);
		for(i = 0;i<g->n;i++)
		{
			fscanf(rf,"%1s",&g->vex[i]);	
		}	
		for(i = 0;i < g->n;i++)
		{
			for(j = 0;j < g->n;j++)
			{
				if(i==j)
				{
					g->edges[i][j] = 0;
				}
				else
				{
					g->edges[i][j] = FINITY;
				}
			}
		}
		for(k = 0;k < g->e;k++)
		{
			fscanf(rf,"%d%d%d",&i,&j,&w);
			g->edges[i][j] = w;
			if(c == 0)
			{
				g->edges[j][i]=w;//c == 0 建立无向图邻接矩阵 
			}
		}
		fclose(rf);
	}
	else
	{
		g->n = 0;	
	} 
}

//利用快速排序方法对边向量进行排序 
void quickSort(edge edges[10])
{
	int i,j,k;
	edge x;
	for(i = 0;i < 9;i++)
	{
		k = i;
		for(j = i+1;j < 10;j++)
		{
			if(edges[j].length < edges[k].length)
			{
				k = j;
			}
		}
		if(k!=i)
		{
			x = edges[k];
			edges[k] = edges[i];
			edges[i] = x;
		}
	}
	printf("sort finished\n");	
} 

//从图的邻接矩阵读取图的所有边信息
void getEdge(Mgraph g,edge edges[])
{
	int i,j,k=0;
	for(i = 0;i < g.n;i++)
	{
		for(j = 0;j < i;j++)
		{
			if(g.edges[i][j]!=0 && g.edges[i][j] < FINITY)
			{
				edges[k].beg = i;
				edges[k].en = j;
				edges[k++].length = g.edges[i][j];	
			}	
		}	
	}	
} 

//kruskal算法求解最小生成树
void kruskal(Mgraph g)
{
	int i,j,k = 0,ltfl;
	int cnvx[M];
	edge edges[M*M]; //存放图的所有边 
	edge tree[M]; //用于存放最小生成树的边信息 
	getEdge(g,edges);
	printf("排序前\n");
	for(i = 0;i < 10;i++)
	{
		printf("(%d->%d   %d)   ",edges[i].beg,edges[i].en,edges[i].length);
	}
	printf("\n");
	quickSort(edges);
	printf("排序后\n");
	for(i = 0;i < 10;i++)
	{
		printf("( %d->%d   %d)   ",edges[i].beg,edges[i].en,edges[i].length);
	}
	for(i = 0;i <g.n;i++)
	{
		cnvx[i] = i;	//设置每一个顶点的联通分量为其顶点编号 
	}
	for(i = 0;i < g.n-1;i++)
	{
		while(cnvx[edges[k].beg] == cnvx[edges[k].en])
		{
			k++;	
		}
		tree[i] = edges[k];
		ltfl = cnvx[edges[k].en];
		for(j = 0;j < g.n;j++)
		{
			if(cnvx[j] == ltfl)
			{
				cnvx[j] == cnvx[edges[k].beg];
			}
		}
		k++;
	} 
	printf("最小生成树是:\n");
	for(j = 0;j < g.n-1;j++)
	{
		printf("%c---%c%6d\n",g.vex[tree[j].beg],g.vex[tree[j].en],tree[j].length);
	}
} 
 

int main()
{
	Mgraph *g = (Mgraph*)malloc(sizeof(Mgraph));
	int i,j;
	char *s = "E://graphinformation.txt";
	create(g,s,0);
	printf("图的节点为:\n**************\n"); 
	for(i = 0;i < g->n;i++)
	{
		printf("%c	",g->vex[i]);
	}
	printf("\n*****************\n\n\n");
	printf("邻接矩阵如下:\n");
	for(i = 0;i < g->n;i++)
	{
		for(j = 0;j < g->n;j++)
		{
			printf("%-4d  ",g->edges[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	kruskal(*g);
	return 0;	
} 

#include <stdio.h>
#include <stdlib.h>
#define M 20

typedef char DataType;//顶点数据类型
//边表结点 
typedef struct node
{
	int adjvex;
	struct node *next;
}EdgeNode;

//头结点 
typedef struct vnode
{
	DataType vertext;
	EdgeNode *FirstEdge;
}VertextNode;

//邻接表 
typedef struct
{
	VertextNode adjList[M];
	int n,e;
}LinkedGraph;

int visited[M];//dfs辅助数组 

//创建图 
void create(LinkedGraph *g,int c)
{
	int i,j,k;
	EdgeNode *s;
	printf("请输入图的边数:\n");
	scanf("%d",&g->e); 
	printf("\n请输入图的顶点数:\n");
	scanf("%d",&g->n);
	for(i = 0 ; i < g->n ; i++)
	{
		printf("\n请输入结点信息:\n");
		scanf("%s",&g->adjList[i].vertext);
		g->adjList[i].FirstEdge = NULL;
	}
	for(k = 0 ; k < g->e ; k++)
	{
		printf("请输入边的信息(数对):\n");
		scanf("%d,%d",&i,&j);
		s = (EdgeNode*)malloc(sizeof(EdgeNode));
		s->adjvex = j;
		s->next = g->adjList[i].FirstEdge;
		g->adjList[i].FirstEdge = s;
		if(c==0)//c=0 建立无向图 
		{
			s = (EdgeNode*)malloc(sizeof(EdgeNode));
			s->adjvex = i;
			s->next = g->adjList[j].FirstEdge;
			g->adjList[j].FirstEdge = s;
		}
	}
}

//从顶点i开始深度优先遍历图的连通分量 
void dfs(LinkedGraph g,int i,int visited[])
{
	EdgeNode *p;
	printf("visit vertext : %c\n",g.adjList[i].vertext);
	p = g.adjList[i].FirstEdge;
	visited[i]=1;
	while(p)
	{
		if(!visited[p->adjvex])
		{
			dfs(g,p->adjvex,visited);
		}
		p=p->next;
	}
 } 

//dfs遍历图 
void DfsTraverse(LinkedGraph g)
{
	int b;
	for(b = 0 ; b < g.n ; b++)
	{
		
		visited[b] = 0;
	}
	for(b = 0 ; b < g.n ; b++)
	{
		if(!visited[b])
		{
			dfs(g,b,visited);
		}
	}
}

//从顶点i出发广度优先遍历g的连通分量 
void bfs(LinkedGraph g,int i)
{
	int j;
	EdgeNode *p;
	int queue[M],front,rear;//FIFO队列
	front=rear=0;
	printf("%c ",g.adjList[i].vertext);
	visited[i] = 1;
	queue[rear++]=i;
	while(rear>front)
	{
		j=queue[front++];
		p=g.adjList[j].FirstEdge;
		while(p)
		{
			if(visited[p->adjvex]==0)
			{
				printf("%c ",g.adjList[p->adjvex].vertext);
				queue[rear++]=p->adjvex;
				visited[p->adjvex]=1;	
			}	
			p=p->next;
		}	
	}	
}

//bfs遍历图 
int BfsTraverse(LinkedGraph g)
{
	int i,count=0;
	for(i=0;i<g.n;i++)
	{
		visited[i]=0;
	}
	for(i = 0;i < g.n;i++)
	{
		if(!visited[i])
		{
			printf("\n");
			count++;
			bfs(g,i);
		}
	}
	return count;
}

int main()
{
	LinkedGraph *g,l;
	g = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	create(g,0);
	l = *g;
	printf("\ndfs遍历序列:\n");
	DfsTraverse(l);
	printf("\nbfs遍历序列:\n");
	BfsTraverse(l);
	return 0;
}


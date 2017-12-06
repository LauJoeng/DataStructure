#include<stdio.h>
#include<malloc.h>
#define M 20
typedef char vertextype;
typedef struct node
{
	int adjvex;
	struct node *next;	
} edgenode;//边结点类型定义 

typedef struct de
{
	edgenode *FirstEdge;
	vertextype vertext;
	int r; //顶点入度 
}vertextnode;//带顶点入度的头结点定义 

typedef struct
{
	vertextnode adjlist[M];
	int n,e;
}AOVGraph;//AOV网络邻接表类型 

//创建图 
void create(AOVGraph *g,int c)
{
	int i,j,k;
	edgenode *s;
	printf("请输入图的边数:\n");
	scanf("%d",&g->e); 
	printf("\n请输入图的顶点数:\n");
	scanf("%d",&g->n);
	for(i = 0 ; i < g->n ; i++)
	{
		printf("\n请输入结点信息:\n");
		scanf("%s",&g->adjlist[i].vertext);
		g->adjlist[i].FirstEdge = NULL;
	}
	for(k = 0 ; k < g->e ; k++)
	{
		printf("请输入边的信息(数对):\n");
		scanf("%d,%d",&i,&j);
		s = (edgenode*)malloc(sizeof(edgenode));
		s->adjvex = j;
		s->next = g->adjlist[i].FirstEdge;
		g->adjlist[i].FirstEdge = s;
		if(c==0)//c=0 建立无向图 
		{
			s = (edgenode*)malloc(sizeof(edgenode));
			s->adjvex = i;
			s->next = g->adjlist[j].FirstEdge;
			g->adjlist[j].FirstEdge = s;
		}
	}
}

//拓扑排序 
int topsort(AOVGraph g)
{
	int k = 0,i,j,v,flag[M];
	int queue[M];
	int front,rear;
	edgenode *p;
	front = 0;
	rear = 0;
	for(i = 0;i < g.n;i++)
	{
		flag[i] = 0;
	}
	for(i = 0;i < g.n;i++)
	{
		if(g.adjlist[i].r == 0 && flag[i] == 0)
		{
			queue[rear++] = i;
			flag[i] = 1;
		}
	}
	printf("\nAOV网的拓扑序列是:\n");
	while(front < rear)
	{
		v = queue[front++];
		printf("%c ",g.adjlist[v].vertext);
		k++;
		p = g.adjlist[v].FirstEdge;
		while(p)
		{
			j = p->adjvex;
			if(--g.adjlist[j].r == 0 && flag[j] == 0)//若顶点入度为0则进队
			{
				queue[rear++]=j;
				flag[j] = 1; 
			} 
			p = p->next;
		}
	}
	return k;
} 


int main()
{
	AOVGraph *g = (AOVGraph*)malloc(sizeof(AOVGraph));
	create(g,1);
	topsort(*g) ;
	return 0;
}
















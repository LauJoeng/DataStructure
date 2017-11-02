#include <stdio.h>
#include <stdlib.h>
#define M 20

typedef char DataType;//������������
//�߱��� 
typedef struct node
{
	int adjvex;
	struct node *next;
}EdgeNode;

//ͷ��� 
typedef struct vnode
{
	DataType vertext;
	EdgeNode *FirstEdge;
}VertextNode;

//�ڽӱ� 
typedef struct
{
	VertextNode adjList[M];
	int n,e;
}LinkedGraph;

int visited[M];//dfs�������� 

//����ͼ 
void create(LinkedGraph *g,int c)
{
	int i,j,k;
	EdgeNode *s;
	printf("������ͼ�ı���:\n");
	scanf("%d",&g->e); 
	printf("\n������ͼ�Ķ�����:\n");
	scanf("%d",&g->n);
	for(i = 0 ; i < g->n ; i++)
	{
		printf("\n����������Ϣ:\n");
		scanf("%s",&g->adjList[i].vertext);
		g->adjList[i].FirstEdge = NULL;
	}
	for(k = 0 ; k < g->e ; k++)
	{
		printf("������ߵ���Ϣ(����):\n");
		scanf("%d,%d",&i,&j);
		s = (EdgeNode*)malloc(sizeof(EdgeNode));
		s->adjvex = j;
		s->next = g->adjList[i].FirstEdge;
		g->adjList[i].FirstEdge = s;
		if(c==0)//c=0 ��������ͼ 
		{
			s = (EdgeNode*)malloc(sizeof(EdgeNode));
			s->adjvex = i;
			s->next = g->adjList[j].FirstEdge;
			g->adjList[j].FirstEdge = s;
		}
	}
}

//�Ӷ���i��ʼ������ȱ���ͼ����ͨ���� 
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

//dfs����ͼ 
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

//�Ӷ���i����������ȱ���g����ͨ���� 
void bfs(LinkedGraph g,int i)
{
	int j;
	EdgeNode *p;
	int queue[M],front,rear;//FIFO����
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

//bfs����ͼ 
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
	printf("\ndfs��������:\n");
	DfsTraverse(l);
	printf("\nbfs��������:\n");
	BfsTraverse(l);
	return 0;
}


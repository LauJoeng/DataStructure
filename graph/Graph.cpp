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

//����ͼ 
void create(LinkedGraph *g,char *fileName,int c)
{
	printf("%s",fileName);
	int i,j,k;
	EdgeNode *s;
	FILE *fp;
	fp = fopen(fileName,"r");
	if(fp)
	{
		fseek(fp,1L,SEEK_SET);
		fscanf(fp,"%d",&g->n);
		fseek(fp,3L,SEEK_SET);
		fscanf(fp,"%d",&g->e);
		printf("\n������=%d,����=%d\n",g->n,g->e);
		printf("\n������Ϣ:\n");
		for(i = 0 ; i < g->n ; i++)
		{
			printf("%c  ",g->adjList[i].vertext);
			fscanf(fp,"%1s",&g->adjList[i].vertext);
			g->adjList[i].FirstEdge = NULL;
		}
		for(k = 0 ; k < g->e ; k++)
		{
			fscanf(fp,"%d%d",&i,&j);
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
		fclose(fp);
	}
	else
	{
		printf("���ļ�ʧ��");
		g->n = 0;
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

void DfsTraverse(LinkedGraph g,int visited[])
{
	int i;
	for(i = 0 ; i < g.n ; i++)
	{
		visited[i]=0;
	}
	for(i = 0 ; i < g.n ; i++)
	{
		if(!visited[i])
		{
			dfs(g,i,visited);
		}
	}
}

int main()
{
	LinkedGraph *g;
	char *f = "C:/Users/Administrator/Desktop/test.txt";
	create(g,f,0);
	return 0;
}


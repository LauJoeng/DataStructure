#include<stdio.h>
#include<malloc.h>
#define M 20
typedef char vertextype;
typedef struct node
{
	int adjvex;
	struct node *next;	
} edgenode;//�߽�����Ͷ��� 

typedef struct de
{
	edgenode *FirstEdge;
	vertextype vertext;
	int r; //������� 
}vertextnode;//��������ȵ�ͷ��㶨�� 

typedef struct
{
	vertextnode adjlist[M];
	int n,e;
}AOVGraph;//AOV�����ڽӱ����� 

//����ͼ 
void create(AOVGraph *g,int c)
{
	int i,j,k;
	edgenode *s;
	printf("������ͼ�ı���:\n");
	scanf("%d",&g->e); 
	printf("\n������ͼ�Ķ�����:\n");
	scanf("%d",&g->n);
	for(i = 0 ; i < g->n ; i++)
	{
		printf("\n����������Ϣ:\n");
		scanf("%s",&g->adjlist[i].vertext);
		g->adjlist[i].FirstEdge = NULL;
	}
	for(k = 0 ; k < g->e ; k++)
	{
		printf("������ߵ���Ϣ(����):\n");
		scanf("%d,%d",&i,&j);
		s = (edgenode*)malloc(sizeof(edgenode));
		s->adjvex = j;
		s->next = g->adjlist[i].FirstEdge;
		g->adjlist[i].FirstEdge = s;
		if(c==0)//c=0 ��������ͼ 
		{
			s = (edgenode*)malloc(sizeof(edgenode));
			s->adjvex = i;
			s->next = g->adjlist[j].FirstEdge;
			g->adjlist[j].FirstEdge = s;
		}
	}
}

//�������� 
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
	printf("\nAOV��������������:\n");
	while(front < rear)
	{
		v = queue[front++];
		printf("%c ",g.adjlist[v].vertext);
		k++;
		p = g.adjlist[v].FirstEdge;
		while(p)
		{
			j = p->adjvex;
			if(--g.adjlist[j].r == 0 && flag[j] == 0)//���������Ϊ0�����
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
















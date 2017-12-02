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

typedef struct edgedata //���ڱ�����С�������ı����Ͷ��� 
{
	int beg,en;//beg,en�Ǳ߶������� 
	int length;//�ߵ�Ȩֵ�� 
}edge;

//����ͼ 
void create(Mgraph *g,char *s,int c)
{
	int i,j,k,w;
	FILE *rf;
	rf = fopen(s,"r");//���ļ��ж�ȡͼ����Ϣ
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
				g->edges[j][i]=w;//c == 0 ��������ͼ�ڽӾ��� 
			}
		}
		fclose(rf);
	}
	else
	{
		g->n = 0;	
	} 
}

//���ÿ������򷽷��Ա������������� 
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

//��ͼ���ڽӾ����ȡͼ�����б���Ϣ
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

//kruskal�㷨�����С������
void kruskal(Mgraph g)
{
	int i,j,k = 0,ltfl;
	int cnvx[M];
	edge edges[M*M]; //���ͼ�����б� 
	edge tree[M]; //���ڴ����С�������ı���Ϣ 
	getEdge(g,edges);
	printf("����ǰ\n");
	for(i = 0;i < 10;i++)
	{
		printf("(%d->%d   %d)   ",edges[i].beg,edges[i].en,edges[i].length);
	}
	printf("\n");
	quickSort(edges);
	printf("�����\n");
	for(i = 0;i < 10;i++)
	{
		printf("( %d->%d   %d)   ",edges[i].beg,edges[i].en,edges[i].length);
	}
	for(i = 0;i <g.n;i++)
	{
		cnvx[i] = i;	//����ÿһ���������ͨ����Ϊ�䶥���� 
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
	printf("��С��������:\n");
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
	printf("ͼ�Ľڵ�Ϊ:\n**************\n"); 
	for(i = 0;i < g->n;i++)
	{
		printf("%c	",g->vex[i]);
	}
	printf("\n*****************\n\n\n");
	printf("�ڽӾ�������:\n");
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

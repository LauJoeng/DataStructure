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

//�Ա������������� 
void Sort(edge edges[],int count)
{
	int i,j,k;
	edge x;
	for(i = 0;i < count-1;i++)
	{
		k = i;
		for(j = i+1;j < count;j++)
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
int getEdge(Mgraph g,edge edges[])
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
	return k;	
} 

//kruskal�㷨�����С������
void kruskal(Mgraph g)
{
	int i,j,k = 0,ltfl,count,h;
	int cnvx[M];
	edge edges[M*M]; //���ͼ�����б� 
	edge tree[M]; //���ڴ����С�������ı���Ϣ 
	count = getEdge(g,edges);
	printf("����ǰ\n");
	for(i = 0;i < 10;i++)
	{
		printf("(%d->%d   %d)   ",edges[i].beg,edges[i].en,edges[i].length);
	}
	printf("\n");
	Sort(edges,count);
	printf("�����\n");
	for(i = 0;i < 10;i++)
	{
		printf("( %d->%d   %d)   ",edges[i].beg,edges[i].en,edges[i].length);
	}
	printf("\n"); 
	for(i = 0;i <g.n;i++)
	{
		cnvx[i] = i;	//����ÿһ���������ͨ����Ϊ�䶥���� 
	}
	for(i = 0;i < g.n-1;i++)
	{
		while(cnvx[edges[k].beg] == cnvx[edges[k].en])
		{
			k++;	//�ҵ�����������ͨ����Ȩ��С�ı� 
		}
		tree[i] = edges[k];//����k������������ 
		ltfl = cnvx[edges[k].en];//��¼ѡ�бߵ��յ���ͨ������� 
		for(j = 0;j < g.n;j++)//������ͨ�����ϲ�Ϊһ����ͨ���� 
		{
			if(cnvx[j] == ltfl)
			{
				cnvx[j] = cnvx[edges[k].beg];
			}
		}
		printf("\n��%d��ѡ���cnvx����:\n",i);
		for(h =0;h < g.n-1;h++)
		{
			printf("%d ",cnvx[h]);	
		} 
		k++;
	} 
	printf("\n*************************************************\n");
//	for(j = 0;j < g.n-1;j++)
//	{
//		printf("(%d--->%d)  ",tree[i].beg,tree[i].en);	
//	} 
	printf("\n��С��������:\n");
	for(j = 0;j < g.n-1;j++)
	{
		printf("%c---%c%6d (%d ---> %d )\n",g.vex[tree[j].beg],g.vex[tree[j].en],tree[j].length,tree[j].beg,tree[j].en);
	}
} 
 

int main()
{
	Mgraph *g = (Mgraph*)malloc(sizeof(Mgraph));
	int i,j;
	char *s = "E://graphinformation.txt";
	create(g,s,0);
	printf("ͼ�Ľڵ�Ϊ:\n******************************************************\n"); 
	for(i = 0;i < g->n;i++)
	{
		printf("%c	",g->vex[i]);
	}
	printf("\n*******************************************************\n\n\n");
	printf("�ڽӾ�������:\n");
	for(i = 0;i < g->n;i++)
	{
		for(j = 0;j < g->n;j++)
		{
			printf("%-4d  ",g->edges[i][j]);
		}
		printf("\n");
	}
	printf("***********************************************************\n\n\n");
	kruskal(*g);
	return 0;	
} 

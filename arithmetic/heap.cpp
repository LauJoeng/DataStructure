#include<stdio.h>
int h[101];// ��Ŷѵ�����
int n;//�洢�ѵĴ�С

void swap(int a,int b)
{
	int t;
	t = h[a];
	h[a] = h[b];
	h[b] = t;
} 

//���µ���,����Ϊ��Ҫ���µ������±� 
void siftdown(int i)
{
	int t,flag=0;//flag��������Ƿ���Ҫ���µ���
	while(i*2<=n&&flag==0)
	{
		if(h[i]>h[i*2])
		{
			t = i*2;
		}
		else
		{
			t = i;
		}
		if(i*2+1<=n)
		{
			if(h[t]>h[i*2+1])
			{
				t = i*2+1;
			}
		}
		if(t!=i)
		{
			swap(t,i);
			i = t;
		}
		else
		{
			flag = 1;
		}
	} 
}

//����
void create()
{
	int i;
	for(i=n/2;i>=1;i--)
	{
		siftdown(i);	
	}
} 

//ɾ�����Ԫ��
int deletemax() 
{
	int t;
	t = h[1];//��¼�Ѷ���ֵ 
	h[1]=h[n];//�����һ��ֵ�����Ѷ�
	n--; 
	siftdown(1);
	return t;
}

int main()
{
	int i,num;
	scanf("%d",&num);
	
	for(i=1;i<=num;i++)
	{
		scanf("%d",&h[i]);
	}
	n = num;
	
	create();
	for(i=1;i<=num;i++)
	{
		printf("%d ",deletemax());
	}
	return 0;
}

/*
14
99 5 36 7 22 17 46 12 2 19 25 28 1 92
*/



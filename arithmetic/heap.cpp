#include<stdio.h>
int h[101];// 存放堆的数组
int n;//存储堆的大小

void swap(int a,int b)
{
	int t;
	t = h[a];
	h[a] = h[b];
	h[b] = t;
} 

//向下调整,参数为需要向下调整的下标 
void siftdown(int i)
{
	int t,flag=0;//flag用来标记是否需要向下调整
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

//建堆
void create()
{
	int i;
	for(i=n/2;i>=1;i--)
	{
		siftdown(i);	
	}
} 

//删除最大元素
int deletemax() 
{
	int t;
	t = h[1];//记录堆顶的值 
	h[1]=h[n];//将最后一个值赋给堆顶
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



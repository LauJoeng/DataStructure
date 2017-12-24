#include<stdio.h>
int main()
{
	int n,m,i,j,k,min,t1,t2,t3;
	int e[7][7],dis[7],book[7]={0};
	int inf=9999999;
	int count=0,sum=0;//count记录生成树顶点个数，sum记录生成树权值
	
	scanf("%d%d",&n,&m);
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j)
			{
				e[i][j] = 0;
			}
			else
			{
				e[i][j] = inf;
			}
		}
	}
	//读入边
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&t1,&t2,&t3);
		e[t1][t2] = t3;
		e[t2][t1] = t3;	
	} 
	//初始化dis数组 
	for(i=1;i<=n;i++)
	{
		dis[i] = e[1][i];
	}
	//prim算法核心部分
	book[1] = 1;//从1号顶点开始
	count++;
	while(count<n)
	{
		min = inf;
		for(i=1;i<=n;i++)
		{
			if(book[i] == 0 && dis[i]<min)
			{
				min = dis[i];
				j = i;
			}
		}
		book[j] = 1;
		count++;
		sum+=dis[j];
		for(k=1;k<=n;k++)
		{
			if(book[k]==0 && dis[k]>e[j][k])
			{
				dis[k] = e[j][k];
			} 
		} 
	}
	
	printf("%d",sum);
	return 0; 
}

/**
6 9
2 4 11
3 5 13
4 6 3
5 6 4
2 3 6
4 5 7
1 2 1
3 4 9
1 3 2
*/

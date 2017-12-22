#include<stdio.h>
#define FINITY 9999999
int min=FINITY,book[101],n,e[101][101];

//cur是当前所在城市编号，dis是当前已经走过的路程 
void dfs(int cur,int dis)
{
	int j;
	if(dis>min)
	{
		return;
	} 
	if(cur==n)
	{
		if(dis<min)
		{
			min = dis;
			printf("min的值变为%d\n",min);
		}
		return;
	}
	for(j=1;j<=n;j++)
	{
		if(e[cur][j]!=FINITY && book[j]==0)
		{
			book[j] = 1;
			dfs(j,dis+e[cur][j]);
			book[j] = 0;//之前一步探索完毕之后，取消对该点的标记 
		}
	}
	return; 
} 

int main()
{
	int i,j,m,a,b,c;
	scanf("%d%d",&n,&m);
	//初始化 
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
				e[i][j] = FINITY;
			}
		}
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		e[a][b] = c;
	}
//	for(i = 1;i<=n;i++)
//	{
//		for(j=1;j<=n;j++)
//		{
//			printf("%8d ",e[i][j]);
//		}
//		printf("\n");
//	}
	book[1] = 1;
	dfs(1,0);//从一号城市出发
	printf("%d",min);//打印一号城市到n号城市的最短路径 
	return 0;
}

/*
5 8
1 2 2
1 5 10
2 3 3
2 5 7
3 1 4
3 4 4
4 5 5
5 3 3
*/




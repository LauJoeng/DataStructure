
//啊哈算法书:迷宫拯救游戏


#include<stdio.h>

struct note
{
    int x,y,f,s;
};
int n,m,p,q,min = 99999999;
int a[51][51],book[51][51];


//深度优先
void dfs(int x,int y,int step)
{
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int tx,ty,k;
    //判断是否到达
    if(x==p && y==q)
    {
        if(step<min)
        {
            min = step;
        }
        return ;
    }
    for(k = 0;k < 4;k++)
    {
        //计算下一个点坐标
        tx = x + next[k][0];
        ty = y + next[k][1];
        if(tx<1 || tx > n|| ty<1 || ty > m)
        {
            continue;
        }
        if(a[tx][ty]==0 && book[tx][ty]==0)
        {
            book[tx][ty] = 1;//标记该点已走过
            dfs(tx,ty,step+1);//继续尝试下一个点
            book[tx][ty] = 0;//尝试结束，取消标记
        }
    }
}

/*
int main()
{
    int i,j,startx,starty;
    scanf("%d%d",&n,&m);//读入地图大小，n行，m列
    for(i = 1;i <= n;i++)
    {
        for(j = 1;j <= m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    scanf("%d%d%d%d",&startx,&starty,&p,&q);
    book[startx][starty] = 1;//标记初始位置
    dfs(startx,starty,0);
    printf("%d",min);
    return 0;
}
*/

int main()
{
    struct note queue[2501];
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int head,tail;
    int i,j,k,n,m,startx,starty,p,q,tx,ty,flag;
    scanf("%d%d",&n,&m);
    for(i = 1;i<=n;i++)
    {
        for(j = 1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    scanf("%d%d%d%d",&startx,&starty,&p,&q);
    head = 1;
    tail = 1;
    queue[tail].x = startx;
    queue[tail].y = starty;
    queue[tail].f = 0;
    queue[tail].s = 0;
    tail++;
    book[startx][starty] = 1;
    flag = 0;//用来标记是否到达目标
    //往四个方向枚举
    while(head<tail)
    {
        for(k=0;k<=3;k++)
        {
            tx = queue[head].x+next[k][0];
            ty = queue[head].y+next[k][1];
            if(tx<1 || tx>n || ty<1 || ty>m)
            {
                continue;
            }
            //判断是否是障碍物或已经在标记列表中
            if(a[tx][ty] == 0 && book[tx][ty] == 0)
            {
                book[tx][ty] = 1;
                queue[tail].x = tx;
                queue[tail].y = ty;
                queue[tail].f = head;//不求路径这句可以忽略
                queue[tail].s = queue[head].s+1;//步数是父亲的步数加1
                tail++;
            }
            if(tx == p && ty == q)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
        {
            break;
        }
        head++;
    }
    printf("%d",queue[tail-1].s);
    return 0;
}

/**
5 4
0 0 1 0
0 0 0 0
0 0 1 0
0 1 0 0
0 0 0 1
1 1 4 3
*/




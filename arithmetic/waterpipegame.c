
//�����㷨:����ˮ��

#include<stdio.h>

int a[51][51];
int book[51][51],flag = 0,n,m;

struct note
{
    int x;
    int y;
}s[100];
int top = 0;

void dfs(int x,int y,int front)
{
    int i;
    //�˴����뵽��(n,m+1)����ɹ�����Ϊ����(n,m)ʱ������һ����һ���ܳ�ȥ
    if(x == n && y == m+1)
    {
        flag = 1;
        for(i=1;i<=top;i++)
        {
            printf("(%d,%d) ",s[i].x,s[i].y);
        }
        return;
    }
    if(x<1 || x>n || y<1 || y>m)
    {
        return;
    }
    if(book[x][y] == 1)
    {
        return;
    }
    book[x][y] = 1;

    top++;
    s[top].x = x;
    s[top].y = y;
    if(a[x][y]>=5 && a[x][y]<=6)
    {
        if(front == 1)
        {
            dfs(x,y+1,1);
        }
        if(front == 2)
        {
            dfs(x+1,y,2);
        }
        if(front == 3)
        {
            dfs(x,y-1,3);
        }
        if(front == 4)
        {
            dfs(x-1,y,4);
        }
    }
    if(a[x][y]>=1 && a[x][y]<=4)
    {
        if(front == 1)
        {
            dfs(x+1,y,2);
            dfs(x-1,y,4);
        }
        if(front == 2)
        {
            dfs(x,y+1,1);
            dfs(x,y-1,3);
        }
        if(front == 3)
        {
            dfs(x+1,y,2);
            dfs(x-1,y,4);
        }
        if(front == 4)
        {
            dfs(x,y+1,1);
            dfs(x,y-1,3);
        }
    }
    book[x][y] = 0;
    return;
}

int main()
{
    int i,j,num = 0;
    scanf("%d%d",&n,&m);
    for(i = 1;i<=n;i++)
    {
        for(j = 1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    dfs(1,1,1);
    if(flag == 0)
    {
        printf("impossible!\n");
    }
    return 0;
}

/*
5 4
5 3 5 3
1 5 3 0
2 3 5 1
6 1 1 5
1 5 5 4
*/

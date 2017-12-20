
//啊哈算法书:炸弹人游戏(利用广度优先遍历进行判断点是否可达)

#include<stdio.h>
struct note
{
    int x;
    int y;
};
char a[20][20];//存储地图

int getnum(int i, int j)
{
    int sum = 0,x,y;
    x = i;
    y = j;
    while(a[x][y]!='#')//判断该点是不是墙，如果不是墙就继续
    {
        if(a[x][y] == 'G')
        {
            sum++;
        }
        x--;
    }
    x = i;
    y = j;
    while(a[x][y]!='#')
    {
        if(a[x][y]=='G')
        {
            sum++;
        }
        x++;
    }
    x = i;
    y = j;
    while(a[x][y]!='#')
    {
        if(a[x][y]=='G')
        {
            sum++;
        }
        y++;
    }
    x = i;
    y = j;
    while(a[x][y]!='#')
    {
        if(a[x][y]=='G')
        {
            sum++;
        }
        y--;
    }
    return sum;
}
int main()
{
    struct note que[401];
    int head,tail;
    int book[20][20] = {0};
    int i,j,k,sum,max = 0,mx,my,n,m,startx,starty,tx,ty;
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    scanf("%d%d%d%d",&n,&m,&startx,&starty);
    for(i = 0;i<=n-1;i++)
    {
        scanf("%s",a[i]);
    }
    head = 1;
    tail = 1;
    que[tail].x = startx;
    que[tail].y = starty;
    tail++;
    book[startx][starty] = 1;
    max = getnum(startx,starty);
    mx = startx;
    my = starty;
    while(head<tail)
    {
        for(k = 0;k<=3;k++)
        {
            tx = que[head].x + next[k][0];
            ty = que[head].y + next[k][1];
            if(tx<1 || tx>n || ty<1 || ty>m)
            {
                continue;
            }
            if(a[tx][ty]=='.'&&book[tx][ty]==0)
            {
                book[tx][ty]=1;
                que[tail].x = tx;
                que[tail].y = ty;
                tail++;

                sum = getnum(tx,ty);
                //如果当前统计出所能消灭敌人数目大于max，则更新max，并用mx，my记录当前坐标
                if(sum > max)
                {
                    max = sum;
                    mx = tx;
                    my = ty;
                }
            }
        }
        head++;//当一个点扩展完成后，必须要head++才能对后面的点进行扩展
    }
    printf("将炸弹放置在(%d,%d)点能消灭的敌人最多%d人\n",mx,my,max);
    return 0;
}

/*
#############
#GG.GGG#GGG.#
###.#G#G#G#G#
#.......#..G#
#G#.###.#G#G#
#GG.GGG.#.GG#
#G#.#G#.#.#.#
##G...G.....#
#G#.#G###.#G#
#...G#GGG.GG#
#G#.#G#G#.#G#
#GG.GGG#G.GG#
#############
*/

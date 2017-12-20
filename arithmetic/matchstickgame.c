
//啊哈算法书:火柴棍游戏

#include<stdio.h>
int fun(int x)
{
    int num = 0;//用来计数
    int f[10] = {6,2,5,5,4,5,6,3,7,6};//用一格数组来记录0-9每个数字需要的火柴棍数目
    while(x/10!=0)//如果x/10不为0的话，说明这个数字至少有两位
    {
        num+=f[x%10];//获得x末尾数字并将此数字所需要的火柴棍数目累加入num中
        x = x/10;
    }
    num+=f[x];//最后一个数字，即第一位
    return num;
}

int main()
{
    int a,b,c,m,i,sum = 0;
    scanf("%d",&m);//读入火柴棍数目
    //开始枚举
    for(a=0;a<=1111;a++)
    {
        for(b = 0;b<=1111;b++)
        {
            c = a+b;
            if(fun(a)+fun(b)+fun(c) == m-4)
            {
                printf("%d+%d=%d\n",a,b,c);
                sum++;
            }
        }
    }
    printf("一共可以拼出%d个不同的等式\n",sum);
    system("pause");
    return 0;
}

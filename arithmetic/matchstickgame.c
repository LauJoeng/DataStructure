
//�����㷨��:������Ϸ

#include<stdio.h>
int fun(int x)
{
    int num = 0;//��������
    int f[10] = {6,2,5,5,4,5,6,3,7,6};//��һ����������¼0-9ÿ��������Ҫ�Ļ�����Ŀ
    while(x/10!=0)//���x/10��Ϊ0�Ļ���˵�����������������λ
    {
        num+=f[x%10];//���xĩβ���ֲ�������������Ҫ�Ļ�����Ŀ�ۼ���num��
        x = x/10;
    }
    num+=f[x];//���һ�����֣�����һλ
    return num;
}

int main()
{
    int a,b,c,m,i,sum = 0;
    scanf("%d",&m);//���������Ŀ
    //��ʼö��
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
    printf("һ������ƴ��%d����ͬ�ĵ�ʽ\n",sum);
    system("pause");
    return 0;
}


//矩阵乘法的实现 
#include<stdio.h>
void mutiply(int a[3][2],int b[2][4],int c[3][4])
{
	int i,j,k,sum=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			sum=0;
			for(k = 0 ; k < 2; k++)
			{
				sum+=a[i][k]*b[k][j];
			} 
			c[i][j]=sum; 
		}
	}
}

int main()
{
	void mutiply(int a[3][2],int b[2][4],int c[3][4]);
	int a[3][2] = 
	{
		1,2,
		3,4,
		5,6
	};
	int b[2][4] = 
	{
		1,2,3,4,
		5,6,7,8
	};
	int c[3][4],i,j;
	mutiply(a,b,c);
	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 4;j++)
		{
			printf("%d  ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}
 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 1000

void char_to_num(char a[],int r[],int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		r[i]=a[i]-'0';
	}
}

int convert(int num[],int result[],int length)
{
	int temp[30];
	int len=length,i,t,k,p,count=0;
	memset(temp,0,sizeof(temp));
	while(len>=1){
		i=0;
		t=0;
		k=0;
		do
		{
			t=t*10+num[i];
			temp[k]=t/2;
			t=t%2;
			i++;
			k++;
		}while(i<len);
		result[count++]=t;
		i=0;
		while((i<k)&&temp[i]==0)i++;
		memset(num,0,sizeof(num));
		k=0;
		for(p=i;p<=len;p++)
			num[k++]=temp[p];
		memset(temp,0,sizeof(temp));
		len=k-1;
	}
	return count;
}

int main()
{
	char s[30];
	int num[30],result[MAX],count=0,i=0;
	while(scanf("%s",s)!=EOF)
	{
		memset(num,0,sizeof(num));
		memset(result,0,sizeof(result));
		char_to_num(s,num,strlen(s));
		count = convert(num,result,strlen(s));
		for(i=count-1;i>=0;i--)
		{
			printf("%d",result[i]);
		}
	}
	return 0;	
} 

#include<stdio.h>
#include<stdlib.h>
#define maxsize 1000

typedef int datatype;
typedef struct
{
	datatype data[maxsize];
	int len;	
} seqlist;

//非递归二分查找
int binsearch1(seqlist s,datatype key)
{
	int low=0,high=s.len-1,mid;
	while(low < high)
	{
		mid = (low + high) / 2;
		if(s.data[mid] == key)
		{
			return mid;	
		}
		if(s.data[mid]>key)
		{
			high = mid - 1;	
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;	
} 

//递归二分查找 
int binsearch2(seqlist s,datatype key,int low, int high)
{
	int mid,k;
	if(low < high)
		return -1;
	else
	{
		mid = (low + high) / 2;
		if(s.data[mid] == key)
		{
			return mid;
		}
		if(s.data[mid] > key)
		{
			return binsearch2(s,key,low,mid - 1);
		}
		else
		{
			return binsearch2(s,key,mid + 1,high);
		}
	}
}


//直接插入排序 
void insertsort(seqlist *s)
{
	printf("\ninsert sort function:\n");
	datatype temp;
	int i,j;
	for(i = 0;i < s->len;i++)
	{
		j = i-1;
		temp = s->data[i];
		while(j != -1&&temp < s->data[j])
		{
			s->data[j+1] = s->data[j];
			j = j-1;
		}
		if(j == -1)
		{
			printf("\n为data[0]赋值: %d\n",temp);
			s->data[0] = temp;
		}
		else
		{
			printf("\n为data[%d]赋值 %d\n",j+1,temp);
			s->data[j+1] = temp;	
		}
	}	
} 

int main()
{
	int i,j;
	seqlist *s;
	s = (seqlist*)malloc(sizeof(seqlist));
	printf("please input number to create data:\n");
	for(i = 0;i < 10;i++)
	{
		scanf("%d",&s->data[i]);
	}
	s->len = 10;
	insertsort(s);
	printf("\n after sort:\n");
	for(i = 0;i < 10;i++)
	{
		printf("%d  ",s->data[i]);
	}
	printf("\n please input number you want to search:\n");
	scanf("%d",&j);
	printf("the index of %d is %d",j,binsearch2(*s,j,0,10));
	return 0;
}






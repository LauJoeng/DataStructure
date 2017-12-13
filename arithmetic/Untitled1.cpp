#include<stdio.h>
#include<string.h>

struct queue
{
	int data[1000];
	int head;
	int tail;
};

struct stack
{
	int data[10];
	int top;
};


int main()
{
	struct queue q1,q2;
	struct stack s;
	int i,flag = 0,book[10],t;
	q1.head = 1;
	q1.tail = 1;
	q2.head = 1;
	q2.tail = 1;
	s.top = 0;
	//��ʼ��������飬���������Щ���Ѿ�������	
	for(i = 1;i <= 6;i++)
	{
		book[i] = 0;
	}
	//�����1���������� 
	for(i = 1;i <= 6;i++)
	{
		scanf("%d",&q1.data[q1.tail++]);
	}
	//�����2���������� 
	for(i = 1;i <= 6;i++)
	{
		scanf("%d",&q2.data[q2.tail++]);
	}
	
	while(q1.head < q1.tail && q2.head < q2.tail)//�����в�Ϊ��ʱִ��ѭ�� 
	{
		t = q1.data[q1.head];//����1���� 
		if(book[t] == 0)//����û������Ϊt����,�򽫶���1��ͷָ���һ�����������Ƽ������� 
		{
			q1.head++;
			s.top++;
			s.data[s.top] = t;
			book[t] = 1;
		} 
		else//����Ӯ�� 
		{
			q1.head++;//�������Ѿ������������β 
			q1.data[q1.tail] = t;
			q1.tail++;
			while(s.data[s.top]!=t)
			{
				book[s.data[s.top]]=0;//�Ѵ���Ƶ�λ�õ�������������ͬ�������Ƽӵ�������	
				q1.data[q1.tail] = s.data[s.top];
				q1.tail++;
				s.top--;				
			} 
		}
		t = q2.data[q2.head];
		if(book[t] == 0)
		{
			q2.head++;
			s.top++;
			s.data[s.top] = t;
			book[t] = 1;
		}
		else
		{
			q2.head++;
			q2.data[q2.tail] = t;
			q2.tail++;
			while(s.data[s.top]!=t)
			{
				book[s.data[s.top]] = 0;
				q2.data[q2.tail] = s.data[s.top];
				q2.tail++;
				s.top--;
			} 
		}
	}
	
	if(q1.head == q1.tail)
	{
		printf("\nС��win\n");
		printf("\n�����е�����:\n");
		for(i = q2.head;i <= q2.tail;i++)
		{
			printf(" %d",q2.data[i]);	
		}	
		if(s.top > 0)
		{
			printf("\n���ϵ�����:\n");
			for(i = 1;i <= s.top;i++)
			{
				printf(" %d",s.data[i]);
			}
		}
		else
		{
			printf("\n�������Ѿ�û����\n");
		}
	} 
	else
	{
		printf("С��win\n");
		printf("\n�����е�����:\n");
		for(i = q1.head;i <= q1.tail;i++)
		{
			printf(" %d",q1.data[i]);	
		}	
		if(s.top > 0)
		{
			printf("\n���ϵ�����:\n");
			for(i = 1;i <= s.top;i++)
			{
				printf(" %d",s.data[i]);
			}
		}
		else
		{
			printf("\n�������Ѿ�û����\n");
		}
	} 
	return 0;
} 






















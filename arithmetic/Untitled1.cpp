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
	//初始化标记数组，用来标记哪些牌已经在桌上	
	for(i = 1;i <= 6;i++)
	{
		book[i] = 0;
	}
	//向队列1插入六张牌 
	for(i = 1;i <= 6;i++)
	{
		scanf("%d",&q1.data[q1.tail++]);
	}
	//向队列2插入六张牌 
	for(i = 1;i <= 6;i++)
	{
		scanf("%d",&q2.data[q2.tail++]);
	}
	
	while(q1.head < q1.tail && q2.head < q2.tail)//当队列不为空时执行循环 
	{
		t = q1.data[q1.head];//队列1出牌 
		if(book[t] == 0)//桌上没有牌面为t的牌,则将队列1的头指针加一，并将这张牌加入桌上 
		{
			q1.head++;
			s.top++;
			s.data[s.top] = t;
			book[t] = 1;
		} 
		else//否则赢牌 
		{
			q1.head++;//这张牌已经打出，会加入队尾 
			q1.data[q1.tail] = t;
			q1.tail++;
			while(s.data[s.top]!=t)
			{
				book[s.data[s.top]]=0;//把打出牌的位置到与打出牌牌面相同的所有牌加到队列中	
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
		printf("\n小哼win\n");
		printf("\n他手中的牌是:\n");
		for(i = q2.head;i <= q2.tail;i++)
		{
			printf(" %d",q2.data[i]);	
		}	
		if(s.top > 0)
		{
			printf("\n桌上的牌是:\n");
			for(i = 1;i <= s.top;i++)
			{
				printf(" %d",s.data[i]);
			}
		}
		else
		{
			printf("\n桌面上已经没牌了\n");
		}
	} 
	else
	{
		printf("小哈win\n");
		printf("\n他手中的牌是:\n");
		for(i = q1.head;i <= q1.tail;i++)
		{
			printf(" %d",q1.data[i]);	
		}	
		if(s.top > 0)
		{
			printf("\n桌上的牌是:\n");
			for(i = 1;i <= s.top;i++)
			{
				printf(" %d",s.data[i]);
			}
		}
		else
		{
			printf("\n桌面上已经没牌了\n");
		}
	} 
	return 0;
} 






















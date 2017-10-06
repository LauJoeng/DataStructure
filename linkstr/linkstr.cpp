#include<stdio.h>
#include<malloc.h>

typedef struct node
{
	char data;
	struct node *next;
}linkstrnode;

typedef linkstrnode *linkstring;

//创建串
void strcreate(linkstring *s)
{
	char ch;
	linkstrnode *p,*r;
	*s = NULL;
	r = NULL;
	while((ch = getchar())!='\n')
	{
		p = (linkstrnode*)malloc(sizeof(linkstrnode));//产生新节点
		p->data = ch;
		if(*s == NULL)
			*s = p;
		else
			r->next = p;
		r = p;
	}
	if(r != NULL)
		r->next=NULL;
}

//串的插入
void strinsert(linkstring *s,int i,linkstring t)
{
	int k;
	linkstring p,q;
	p = *s;
	k = 1;
	while(p && k < i-1)
	{
		p = p->next;
		k++;
	}
	if(!p)
		printf("error!\n");
	else
	{
		q = t;
		while(q && q->next)
			q = q->next;//用q查找t中最后一个元素
		q->next = p->next;//将t连接到s中第i个位置上
		p->next = t;
	}
}

//串的删除
void strdelete(linkstring *s,int i,int len)
{
	int k;
	linkstring p,q,r;
	p = *s;
	q = NULL;
	k = 1;
	while(p&&k<i)
	{
		q = p;
		p = p->next;
		k++;
	}//用p查找s的第i个元素，用q始终跟踪p的前驱

	if(!p)
		printf("error!\n");
	else
	{
		k = 1;
		while(k < len && p)
		{
			p = p->next;
			k++;
		}//p从第i个元素开始查找长度为len子串的最后位置
		if(!p)
			printf("error2!\n");
		else
		{
			if(!q)//被删除的子串位于s的最前面
			{
				r = *s;
				*s = p->next;
			}
			else
			{
				r = q->next;
				q->next = p->next;
			}
			p->next = NULL;
			while(r!=NULL)//回收被删除的子串所占的空间
			{
				p = r;
				r = r->next;
				free(p);
			}
		}
	}

}

//串的连接
void strcontact(linkstring *s1,linkstring s2)
{
	linkstring p;
	if(!*s1)
	{
		*s1 = s2;
		return;
	}
	else
	{
		if(s2)
		{
			p = *s1;
			while(p->next)
				p = p->next;
			p->next = s2;
		}
	}
}

//求子串
linkstring substring(linkstring s,int i,int len)
{
	int k;
	linkstring p,q,r,t;
	p = s;
	k = 1;
	while(p && k < i)
	{
		p = p->next;
		k++;
	}
	if(!p)
	{
		printf("error!\n");
		return NULL;
	}
	else
	{
		r = (linkstring)malloc(sizeof(linkstrnode));
		r->data = p->data;
		r->next = NULL;
		k = 1;
		q = r;
		while(p->next && k < len)
		{
			p = p->next;
			k++;
			t = (linkstring)malloc(sizeof(linkstrnode));
			t->data = p->data;
			q->next = t;
			q=t;
		}
		if(k < len)
		{
			printf("error2!\n");
			return NULL;
		}
		else
		{
			q->next = NULL;
			return r;
		}
	}

}

//输出字符串
void displaystr(linkstring *s)
{
	linkstring p;
	p = *s;
	while(p)
	{
		printf("%c",p->data);
		p = p->next;
	};
	printf("\n");
}

int index(seq)

void main()
{
	linkstring *s = (linkstring*)malloc(sizeof(linkstrnode)),*p= (linkstring*)malloc(sizeof(linkstrnode));
	printf("请输入字符串，以回车结尾:\n");
	strcreate(s);
	printf("输入的字符串为:\n");
	displaystr(s);
	printf("请再次一个输入字符串，以回车结尾:\n");
	strcreate(p);
	printf("输入的字符串为:\n");
	displaystr(p);
//	printf("删除测试,删除位置3长度为4的子串后字符串为:\n");
//	strdelete(s,3,4);
//	displaystr(s);
	printf("将第二个字符串插入第一个字符串的第2个位置后字符串为:\n");
	strinsert(s,2,*p);
	displaystr(s);
}




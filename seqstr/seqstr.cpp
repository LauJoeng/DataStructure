//串的顺序存储

#define MAXSIZE 100
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct
{
	char str[MAXSIZE];
	int length;
}seqstring;

/**
*串的插入
*/
void strinsert(seqstring *s,int i,seqstring T)
{
	int k;
	if(i < 1 || i > s->length+1 || s->length + T.length > MAXSIZE -1)
		printf("cannot insert!\n");
	else 
	{
		for(k = s->length-1 ; k >= i-1 ; k--)
		{
			s->str[T.length+k] = s->str[k];
		}
		for(k = 0 ; k < T.length ; k++)
		{
			s->str[i+k-1] = T.str[k];
		}
		s->length += T.length;
		s->str[s->length] = '\0';
	}
}

/**
*串的删除
*/

void strdelete(seqstring *s,int i,int len)
{
	int k;
	if(i < 1 || i > s->length || i +len - 1 > s->length)
		printf("cannot delete!\n");
	else 
	{
		for(k = i + len - 1 ; k < s->length ; k++)
		{
			s->str[k-len] = s->str[k];
		}
		s->length-=len;
		s->str[s->length] = '\0';
	}
}

//输出串
void displaystring(seqstring *s)
{
	int k;
	for(k = 0 ; k < s->length-1 ; k++)
	{
		printf("%c",s->str[k]);
	}
}

//朴素模式匹配子串,p为子串，t为主串
int index(seqstring p,seqstring t)
{
	int i,j,succ;
	i = 0;
	succ = 0;//成功的标志
	while((i <= t.length-p.length) && (!succ))
	{
		j = 0;
		succ = 1;
		while(j <= p.length - 1 && succ)
		{
			if(p.str[j] == t.str[i+j])
			{
			//	printf("%c,%c     ",p.str[j],t.str[i+j]);
				j++;
			}
			else
				succ = 0;
		}
		i++;
	}
	if(succ)
		return (i-1);
	else
		return -1;
}

void main()
{
	int i = 0;
	char ch;
	seqstring *s = (seqstring*)malloc(sizeof(seqstring)), *p= (seqstring*)malloc(sizeof(seqstring));
	printf("请输入主串，以回车结束:\n");
	while((ch = getchar())!='\n')
	{
		s->str[i] = ch;
		i++;
	}
	s->str[++i] = '\0';
	s->length = strlen(s->str) -1;
	i = 0;
	printf("\n请输入子串，以回车结束:\n");
	while((ch = getchar())!='\n')
	{
		p->str[i] = ch;
		i++;
	}
	p->str[++i] = '\0';
	p->length = strlen(p->str) - 1;
/*	printf("删除前str为:\n",s->str);
	displaystring(s);
	printf("\n");
	strdelete(s,3,4);
	printf("删除后:\n");
	displaystring(s);
	printf("\n");*/
	printf("测试朴素模式匹配字符串:子串首次出现的位置是:\n");
	printf("%d\n",index(*p,*s));

}



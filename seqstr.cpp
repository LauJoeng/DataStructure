//����˳��洢

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
*���Ĳ���
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
*����ɾ��
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

//�����
void displaystring(seqstring *s)
{
	int k;
	for(k = 0 ; k < s->length-1 ; k++)
	{
		printf("%c",s->str[k]);
	}
}

//����ģʽƥ���Ӵ�,pΪ�Ӵ���tΪ����
int index(seqstring p,seqstring t)
{
	int i,j,succ;
	i = 0;
	succ = 0;//�ɹ��ı�־
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
	printf("�������������Իس�����:\n");
	while((ch = getchar())!='\n')
	{
		s->str[i] = ch;
		i++;
	}
	s->str[++i] = '\0';
	s->length = strlen(s->str) -1;
	i = 0;
	printf("\n�������Ӵ����Իس�����:\n");
	while((ch = getchar())!='\n')
	{
		p->str[i] = ch;
		i++;
	}
	p->str[++i] = '\0';
	p->length = strlen(p->str) - 1;
/*	printf("ɾ��ǰstrΪ:\n",s->str);
	displaystring(s);
	printf("\n");
	strdelete(s,3,4);
	printf("ɾ����:\n");
	displaystring(s);
	printf("\n");*/
	printf("��������ģʽƥ���ַ���:�Ӵ��״γ��ֵ�λ����:\n");
	printf("%d\n",index(*p,*s));

}



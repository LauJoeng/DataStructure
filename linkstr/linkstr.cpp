#include<stdio.h>
#include<malloc.h>

typedef struct node
{
	char data;
	struct node *next;
}linkstrnode;

typedef linkstrnode *linkstring;

//������
void strcreate(linkstring *s)
{
	char ch;
	linkstrnode *p,*r;
	*s = NULL;
	r = NULL;
	while((ch = getchar())!='\n')
	{
		p = (linkstrnode*)malloc(sizeof(linkstrnode));//�����½ڵ�
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

//���Ĳ���
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
			q = q->next;//��q����t�����һ��Ԫ��
		q->next = p->next;//��t���ӵ�s�е�i��λ����
		p->next = t;
	}
}

//����ɾ��
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
	}//��p����s�ĵ�i��Ԫ�أ���qʼ�ո���p��ǰ��

	if(!p)
		printf("error!\n");
	else
	{
		k = 1;
		while(k < len && p)
		{
			p = p->next;
			k++;
		}//p�ӵ�i��Ԫ�ؿ�ʼ���ҳ���Ϊlen�Ӵ������λ��
		if(!p)
			printf("error2!\n");
		else
		{
			if(!q)//��ɾ�����Ӵ�λ��s����ǰ��
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
			while(r!=NULL)//���ձ�ɾ�����Ӵ���ռ�Ŀռ�
			{
				p = r;
				r = r->next;
				free(p);
			}
		}
	}

}

//��������
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

//���Ӵ�
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

//����ַ���
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
	printf("�������ַ������Իس���β:\n");
	strcreate(s);
	printf("������ַ���Ϊ:\n");
	displaystr(s);
	printf("���ٴ�һ�������ַ������Իس���β:\n");
	strcreate(p);
	printf("������ַ���Ϊ:\n");
	displaystr(p);
//	printf("ɾ������,ɾ��λ��3����Ϊ4���Ӵ����ַ���Ϊ:\n");
//	strdelete(s,3,4);
//	displaystr(s);
	printf("���ڶ����ַ��������һ���ַ����ĵ�2��λ�ú��ַ���Ϊ:\n");
	strinsert(s,2,*p);
	displaystr(s);
}




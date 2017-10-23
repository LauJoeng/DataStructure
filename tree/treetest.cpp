#include<stdio.h>
#include<malloc.h>
#define m 3
typedef char datatype;

//ָ�뺢�ӱ�ʾ 
typedef struct node
{
	datatype data;
	struct node *child[m];	
} node ,*tree;

//��ǰ�����˳����һ�Ŷ���Ϊ3����
tree createtree()
{
	int i;
	char ch;
	tree t;
	if((ch = getchar())=='#')
		t = NULL;
	else
	{
		t = (tree)malloc(sizeof(node));
		t->data = ch;
		for(i = 0 ; i < m ; i++)
		{
			t->child[i] = createtree();
		}
	}
	return t;	
}

//ǰ�����
void preorder(tree p)
{
	int i;
	if(p != NULL)
	{
		printf("%c -> ",p->data);
		for(i = 0 ; i < m ; i++)
		{
			preorder(p->child[i]);
		}	
	}	
} 
	
int main()
{ 
	tree t = createtree();
	printf("\n��������ϣ���ʼ����!\n");
	preorder(t);
	return 0;
}


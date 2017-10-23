#include<stdio.h>
#include<malloc.h>
#define m 3
typedef char datatype;

//指针孩子表示 
typedef struct node
{
	datatype data;
	struct node *child[m];	
} node ,*tree;

//按前序遍历顺序建立一颗度数为3的树
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

//前序遍历
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
	printf("\n树创建完毕，开始遍历!\n");
	preorder(t);
	return 0;
}


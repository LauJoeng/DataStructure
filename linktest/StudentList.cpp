#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	char num[10];
	char name[10];
	char phoneNum[11];
	int sex;
	student *next;
}DataType;


typedef struct node
{
	DataType data;
	struct node *next;
}Lnode,*LinkList;


void printList(Lnode *head);
/*输出菜单*/
void menu()
{
	printf("\n**********    通讯录管理系统    ***********\n");
	printf("\n\n   =====================================  \n\n");
	printf("\n          0.退出系统.             \n");
	printf("\n          1.创建链表.             \n");
	printf("\n          2.插入学生数据.             \n");
	printf("\n          3.删除学生数据.             \n");
	printf("\n          4.根据学号查询.             \n");
	printf("\n          5.输出链表数据             \n");
	printf("\n          6.清空数据.             \n");
	printf("\n   =====================================");
	printf("\n\n请选择:\n");
}

int isNumExist(Lnode *head,char *num)
{
	int isExist = 0;
	Lnode *p = head;
	while(p->next != NULL)
	{
		p = p->next;
		if(strcmp(num,p->data.num) == 0)
		{
			isExist = 1;
			break;
		}
	}
	return isExist;
}


/*输出链表*/
void printList(Lnode *head)
{
	Lnode *p = head;
	while(p->next != NULL)
	{
		
		p = p->next;
		printf("\n***************************\n");
		printf("\n学号:%s\n",p->data.num);
		printf("\n姓名:	%s\n",p->data.name);
		printf("\n联系电话: %s\n",p->data.phoneNum);
		printf("\n性别:%c\n\n\n",p->data.sex == 1?'女':'男');
	}
}

void scanf_list(LinkList &head,int len)
{
	Lnode *p,*q;
	int i = 0;
	head = (LinkList)malloc(sizeof(Lnode));
	head->next = NULL;
	q = head;
	while(i < len)
	{
		p = (Lnode*)malloc(sizeof(Lnode));
		p->next = NULL;
		printf("\n请输入第%d个学生的学号:\n",(i+1));
		while(1)
		{
			scanf("%s",p->data.num);
			if(isNumExist(head,p->data.num))
			{
				printf("\n学号已存在，请重新输入!\n");
			}
			else
				break;
		}
		printf("\n请输入第%d个学生的姓名:\n",(i+1));
		scanf("%s",p->data.name);
		printf("\n请输入第%d个学生的联系电话:\n",(i+1));
		scanf("%s",p->data.phoneNum);
		printf("\n请输入第%d个学生的性别(0为男，1为女):\n",(i+1));
		while(1)
		{
			scanf("%d",&p->data.sex);
			if(p->data.sex == 0 || p->data.sex == 1)
			{
				break;
			}
			else
				printf("\n性别选择错误! 请重新输入:\n");
		}
		q->next = p;
		q = q->next;
		i++;
	}
	q->next = NULL;
}

/*获取链表长度*/
int getListLength(LinkList head)
{
	int i = 0;
	Lnode *p;
	p = head;
	if(!p)
	{
		return 0;
	}
	while(p->next)
	{
		i++;
		p = p->next;
	}
	return i;
}


/*插入学生*/
void insert(Lnode *head)
{
	Lnode *p,*q;
	p = head;
	q = (Lnode*)malloc(sizeof(node));
	printf("\n请输入要插入学生的学号:\n");
	while(1)
	{
		scanf("%s",q->data.num);
		if(isNumExist(head,q->data.num))
		{
			printf("\n学号已存在，请重新输入!\n");
		}
		else
			break;
	}
	printf("\n请输入要插入学生的姓名:\n");
	scanf("%s",q->data.name);
	printf("\n请输入要2插入学生的联系方式:\n");
	scanf("%s",q->data.phoneNum);
	printf("\n请输入要插入学生的性别(0为男，1为女):\n");
	while(1)
	{
		scanf("%d",&p->data.sex);
		if(p->data.sex == 0 || p->data.sex == 1)
		{
			break;
		}
		else
			printf("\n性别选择错误! 请重新输入:\n");
	}
	q->next = head->next;
	p->next = q;
	printf("\n插入成功!\n");
}

/*根据学号查询学生所处链表位置*/
int getStuLocalByNum(Lnode *head,char *num)
{
	int i = 0;
	Lnode *p;
	p = head;
	
	while(strcmp(num,p->data.num)!=0 && p != NULL)
	{
		p = p->next;
		i++;
	}
	return i;
}

/*根据位置获取学生*/
Lnode *getStuByLocal(Lnode *head,int i)
{
	Lnode *p;
	int currLocal = 0;
	p = head;
	while(currLocal != i)
	{
		p = p->next;
		currLocal++;
	}
	return p;
}


/*删除学生*/
int remove(Lnode *head)
{
	int i = -1;
	char num[10];
	Lnode *stu,*preStu;
	printf("\n请输入要删除学生的学号(10位数字):\n");
	scanf("%s",num);
	i = getStuLocalByNum(head,num);
	if(i > getListLength(head) || i <0)
	{
		return 0;
	}
	stu = getStuByLocal(head,i+1);
	if(i - 1 < 0)
	{
		head->next = stu->next;
		return 1;
	}
	preStu = getStuByLocal(head,i);
	preStu->next = stu->next;
	free(stu);
	return 1;
}

void queryStuByNum(Lnode *head)
{
	char num[10];
	Lnode *stu;
	printf("\n请输入要查询学生的学号:\n");
	scanf("%s",num);
	stu = getStuByLocal(head,getStuLocalByNum(head,num));
	printf("\n查询到学生信息如下:\n");
	printf("\n姓名: %s\n",stu->data.name);
	printf("\n学号: %s\n",stu->data.num);
	printf("\n联系方式: %s\n",stu->data.phoneNum);
	printf("\n性别: %d\n",stu->data.sex);
}

int main()
{
	int menu_select,length = 0,flag = 0;
	Lnode *head = NULL;
	menu();
	while(1)
	{
		scanf("%d",&menu_select);
		if(menu_select == 0)
		{
			break;
		}
		else
		{
			if(menu_select != 1 && getListLength(head) <= 0)
				{
					printf("\n链表不存在,请先创建!\n");
				}
				else
				{
					switch(menu_select)
					{
					case 1:
					printf("\n请输入链表长度:\n");
					while(length <= 0)
					{
						scanf("%d",&length);
						if(length < 0)
						{
							printf("\n请输入正确的长度!\n");
						}
					}
					scanf_list(head,length);
					break;
				case 2:
					insert(head);	
					break;
				case 3:
					flag = remove(head);
					if(flag)
					{
						printf("\n删除成功,请继续操作!\n");
						printf("\n删除完成后链表如下:{\n");
						printList(head);
						printf("}\n");
					}
					else
						printf("\n删除失败，学生不存在!");
					break;
				case 4:
					queryStuByNum(head);
					break;
				case 5:
					printList(head);
					break;
				default:
					printf("\n请正确输入!\n");
					break;
				}
			}
		}
		system("pause");
		system("CLS");
		printf("\n");
		menu();
	}
	return 0;
}

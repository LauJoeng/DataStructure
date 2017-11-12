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
/*����˵�*/
void menu()
{
	printf("\n**********    ͨѶ¼����ϵͳ    ***********\n");
	printf("\n\n   =====================================  \n\n");
	printf("\n          0.�˳�ϵͳ.             \n");
	printf("\n          1.��������.             \n");
	printf("\n          2.����ѧ������.             \n");
	printf("\n          3.ɾ��ѧ������.             \n");
	printf("\n          4.����ѧ�Ų�ѯ.             \n");
	printf("\n          5.�����������             \n");
	printf("\n          6.�������.             \n");
	printf("\n   =====================================");
	printf("\n\n��ѡ��:\n");
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


/*�������*/
void printList(Lnode *head)
{
	Lnode *p = head;
	while(p->next != NULL)
	{
		
		p = p->next;
		printf("\n***************************\n");
		printf("\nѧ��:%s\n",p->data.num);
		printf("\n����:	%s\n",p->data.name);
		printf("\n��ϵ�绰: %s\n",p->data.phoneNum);
		printf("\n�Ա�:%c\n\n\n",p->data.sex == 1?'Ů':'��');
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
		printf("\n�������%d��ѧ����ѧ��:\n",(i+1));
		while(1)
		{
			scanf("%s",p->data.num);
			if(isNumExist(head,p->data.num))
			{
				printf("\nѧ���Ѵ��ڣ�����������!\n");
			}
			else
				break;
		}
		printf("\n�������%d��ѧ��������:\n",(i+1));
		scanf("%s",p->data.name);
		printf("\n�������%d��ѧ������ϵ�绰:\n",(i+1));
		scanf("%s",p->data.phoneNum);
		printf("\n�������%d��ѧ�����Ա�(0Ϊ�У�1ΪŮ):\n",(i+1));
		while(1)
		{
			scanf("%d",&p->data.sex);
			if(p->data.sex == 0 || p->data.sex == 1)
			{
				break;
			}
			else
				printf("\n�Ա�ѡ�����! ����������:\n");
		}
		q->next = p;
		q = q->next;
		i++;
	}
	q->next = NULL;
}

/*��ȡ������*/
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


/*����ѧ��*/
void insert(Lnode *head)
{
	Lnode *p,*q;
	p = head;
	q = (Lnode*)malloc(sizeof(node));
	printf("\n������Ҫ����ѧ����ѧ��:\n");
	while(1)
	{
		scanf("%s",q->data.num);
		if(isNumExist(head,q->data.num))
		{
			printf("\nѧ���Ѵ��ڣ�����������!\n");
		}
		else
			break;
	}
	printf("\n������Ҫ����ѧ��������:\n");
	scanf("%s",q->data.name);
	printf("\n������Ҫ2����ѧ������ϵ��ʽ:\n");
	scanf("%s",q->data.phoneNum);
	printf("\n������Ҫ����ѧ�����Ա�(0Ϊ�У�1ΪŮ):\n");
	while(1)
	{
		scanf("%d",&p->data.sex);
		if(p->data.sex == 0 || p->data.sex == 1)
		{
			break;
		}
		else
			printf("\n�Ա�ѡ�����! ����������:\n");
	}
	q->next = head->next;
	p->next = q;
	printf("\n����ɹ�!\n");
}

/*����ѧ�Ų�ѯѧ����������λ��*/
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

/*����λ�û�ȡѧ��*/
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


/*ɾ��ѧ��*/
int remove(Lnode *head)
{
	int i = -1;
	char num[10];
	Lnode *stu,*preStu;
	printf("\n������Ҫɾ��ѧ����ѧ��(10λ����):\n");
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
	printf("\n������Ҫ��ѯѧ����ѧ��:\n");
	scanf("%s",num);
	stu = getStuByLocal(head,getStuLocalByNum(head,num));
	printf("\n��ѯ��ѧ����Ϣ����:\n");
	printf("\n����: %s\n",stu->data.name);
	printf("\nѧ��: %s\n",stu->data.num);
	printf("\n��ϵ��ʽ: %s\n",stu->data.phoneNum);
	printf("\n�Ա�: %d\n",stu->data.sex);
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
					printf("\n��������,���ȴ���!\n");
				}
				else
				{
					switch(menu_select)
					{
					case 1:
					printf("\n������������:\n");
					while(length <= 0)
					{
						scanf("%d",&length);
						if(length < 0)
						{
							printf("\n��������ȷ�ĳ���!\n");
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
						printf("\nɾ���ɹ�,���������!\n");
						printf("\nɾ����ɺ���������:{\n");
						printList(head);
						printf("}\n");
					}
					else
						printf("\nɾ��ʧ�ܣ�ѧ��������!");
					break;
				case 4:
					queryStuByNum(head);
					break;
				case 5:
					printList(head);
					break;
				default:
					printf("\n����ȷ����!\n");
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

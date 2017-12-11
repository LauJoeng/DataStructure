#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAXSIZE 770
#define MAX 1000
typedef struct node{
	int data;//Ȩֵ 
	struct node *lchild,*rchild,*parents,*next;
}hufnode;//Huffman���������
 
typedef hufnode* linkhuf;

typedef struct{
	linkhuf key[MAXSIZE];
	int length;
}recond; //����shell������ʱ�����ṹ�� 

typedef struct code{
	char c[20];//�洢���� 
	int weight;//Ȩֵ 
	char ch[3];//�ַ� 
	int length;//���볤�� 
	linkhuf address;//�洢ÿ������ַ���Ա��ҵ�ÿһ��Ҷ�ӽ��ı��� 
}code;

typedef struct count{
	char info[3];	//�洢�ֽڣ���Ϊ���ܴ��ں��֣���˲����ַ����洢 
	int num;		//���ֽڳ���Ƶ�� 
	struct count *next;
}count;//ͳ���ַ�Ƶ������������ 

typedef struct codetext{
	char ch[MAX][3];
	int length;
}codetext;//�洢�ı��ַ�������� 


//����ͳ���ַ�Ƶ�ʵ������ͷ���
count* Init( )									
{
	count *head;
	head=(count*)malloc(sizeof(count));
	head->next=NULL;
	return (head);
}

//ͳ���ַ�Ƶ�� 
void Statistics(char *c,count *head)
{
	int flag=1,a;
	count *p;
	p=head->next;
	while(p!=NULL&&flag==1)	//���ж�ȡ�����ַ����ѽ������ַ�����ıȽϡ�
	{
		a=strcmp((p->info),c);
		if(a==0)
			flag=0;
		else
			p=p->next;
	}
	if(flag==0)		//���Ѵ��ڶ�ȡ�����ַ�������м�һ��
		p->num++;
	else 			//�������½������
	{
		p=(count*)malloc(sizeof(count));
		strcpy(p->info,c);
		p->num=1;
		p->next=head->next;
		head->next=p;//���½ڵ���뵽��һ���ڵ�λ�� 
	}
}

//ͳ���ı����ַ���Ƶ��
void Statistics_Frequency(count *head)						
{
	FILE *fp;
	int i=0,j=0;
	char c[3];
	if((fp=fopen("E:\\code\\testfile.txt","r"))==NULL)
	{
		printf("���ļ�ʧ��\n");
		printf("%4d",ferror(fp));
		exit(0);
	}
	while(!feof(fp)) //ͳ�ƴ������ı����ֽ���
	{
		c[0]=fgetc(fp);
		i++;
	}
	i=i-1;
	rewind(fp);
	while(j<i)											
	{
		fgets(c,3,fp);		//���ں����������ֽڱ�ʾ������ÿ�ζ�ȡǰ�����ֽڣ��������ֽ��Զ���'\0'
		j=j+2;
		if(c[0]<0&&c[1]<0)	//�����ڼ�����б�ʾΪ�����������ж��Ƿ�Ϊ���ֺ���ĸ�Լ�����
			Statistics(c,head);
		else 
		{
			if(c[0]=='\n')	//�س��ͻ��з��ڼ������ʾΪ�����ֽڣ����������ƶ��ļ�λ�ñ��
			{
			
			}
			else//���˻��з����⣬������ĸ�������ڼ�����б�ʾΪһ���ֽڣ����������ƶ��ļ�λ�ñ��һ��
			{
				fseek(fp,-1,1);
				j=j-1;
			}
			c[1]='\0';
			Statistics(c,head);	//�Ƚ϶�ȡ�����ַ��Ƿ����ѽ������ַ�������
		}
	}
	fclose(fp);
}

//��ͳ�Ƶ��ַ���Ƶ��д���ı���
void Write_Frequency(count *head)   
{
	count *p;
	FILE *fp;
	char c[20]="���ַ�Ƶ��Ϊ��",ch='\n';
	int i=0;
	if((fp=fopen("E:\\code\\characater_frequency.txt","w"))==NULL)
	{
		printf("���ı��ĸ����ַ���Ƶ��.txt��ʧ��\n");
		printf("ʧ�ܵ�ԭ��\n");
		printf("%4d",ferror(fp));
		exit(0);
	}
	p=head->next;
	while(p!=NULL)
	{
		fputs(p->info,fp);
		fputs(c,fp);
		fprintf(fp,"%d  ",p->num);
		i++;
		if((i%5)==0)
			fputc(ch,fp);
		p=p->next;
	}
	fclose(fp);
}

//���ַ���Ƶ��д����find[maxisize].weight��,ָ��j�����ַ����� 
void Read_Weight_Value(count *head,code *find,int *j)
{
	count *p;
	p=head->next;
	while(p!=NULL)
	{
		strcpy(find[*j].ch,p->info);
		find[*j].weight=p->num;
		*j=*j+1;
		p=p->next;
	}
	*j=*j-1;//���һ���ַ�Ϊ������ 
}

//��ʼ��Huffman�� 
linkhuf Creat_Head()			
{
	linkhuf head;
	head=(linkhuf)malloc(sizeof(hufnode));
	head->next=NULL;
	head->rchild=NULL;
	head->lchild=NULL;
	head->parents=NULL;
	return head;
}

//��ʼ�����������������
void Assingment(linkhuf head,code find[MAXSIZE],int j)				
{
	int i;
	linkhuf p = head,q;
	for(i=1;i<=j;i++)
	{
//		Append(p,find[i].weight);
//		find[i].address=head->next;	//��ÿһ�����ĵ�ַ��ֵ��find[i].address���Ա��ں����ҵ�ÿһ��Ҷ�ӽ��ı��롣
		q = (linkhuf)malloc(sizeof(hufnode));
		q->data = find[i].weight;
		q->lchild = NULL;
		q->rchild = NULL;
		q->parents = NULL;
		q->next = head->next;
		head->next = q;
		find[i].address = q;
	}
}

//���������ݰ�Ȩֵ����shell���� 
void Shelt_Sort(linkhuf head)
{
	recond m;
	linkhuf a=head,p=head->next,q;
	int i,j,k=1,d;
	while(p!=NULL)
	{
		m.key[k++]=p;
		p=p->next;
	}
	m.length=k-1;
	d=m.length/2;
	do
	{
		for(i=d+1;i<=m.length;i++)//�ӵ�d+1��Ԫ�ؿ�ʼ��������Ԫ����������Ӧ������ 
		{
			m.key[0]=m.key[i];//�����i��Ԫ�� 
			j=i-d;//��ǰ�Ҳ���λ�� 
			while(j>0&&m.key[0]->data<m.key[j]->data)//������Ƚ��Ҳ���λ�� 
			{
				m.key[j+d]=m.key[j];//��¼���� 
				j=j-d;//������ǰ���� 
			}
			m.key[j+d]=m.key[0];//�����i��Ԫ�صĸ��� 
		}
		d=d/2;
	}while(d>=1);
	head->next=m.key[1];	//���ź���Ľ��ĵ�һ����ַ����ͷ����next��
	q=head->next;	//����һ�����ĵ�ַ����q��
	i=2;
	p=m.key[i];
	while(i<=m.length)	//�����ź���ĵ�ַ����������next��
	{
		q->next=p;
		q=q->next;
		p=m.key[i];
		i++;
	}
	q->next=p;
	q->next->next=NULL;
}

//���������õ�Ȩֵ
void Display(linkhuf head)								
{
	linkhuf p;
	p=head->next;
	printf("�ѽ��������Ȩֵ����:\n");
	while(p!=NULL)
	{
		printf("%4d",p->data);
		p=p->next;
	}
}

//���������������Ĳ��뺯��
linkhuf Insert(linkhuf root,linkhuf s)  
{
	linkhuf p1,p2;
	p1=root;
	if(root==NULL) 
		root=s;
	else
	{
		p2=NULL;
		p1=root;
		while(p1&&(s->data>p1->data))
		{
			p2=p1;
			p1=p1->next;
		}
		s->next=p1;
		if(p2==NULL)
			root=s;
		else
			p2->next=s;
	}
	return root;
}

//����������ĺ���
linkhuf Creat_Huffman(linkhuf root)						
{	linkhuf rl,rr,s;
	while(root&&root->next)
	{
		rl=root;
		rr=root->next;
		root=rr->next;
		s=(linkhuf)malloc(sizeof(hufnode));
		s->lchild=rl;
		s->rchild=rr;
		rl->parents=s;
		rr->parents=s;
		s->next=NULL;
		s->data=rr->data+rl->data;
		root=Insert(root,s);
	}
	root->parents=NULL;
	return (root);
}

//ǰ�������������
void Pre_Order(linkhuf head)									
{
	if(head!=NULL)
	{
		printf("%4d\n",head->data);
		Pre_Order(head->lchild);
		Pre_Order(head->rchild);
	}
}

//���й��������룬�洢��find[maxsize].c��
void Find_Code(linkhuf head,code find[MAXSIZE],int j)
{
	int weight;
	int i,k;
	linkhuf p,q;
	for(k=1;k<=j;k++)
	{
		weight=find[k].weight;									
		p=find[k].address;	//����find[k].address�洢��Ҷ�ӽ��ĵ�ַ��
		q=p->parents;	//���ݸ�ĸ�׵Ľ�������ҵ�����㡣
		i=1;
		while(q!=NULL)
		{
			if(q->lchild==p)
			{
				find[k].c[i]='0';
				i++;
			}
			else if(q->rchild==p)
			{
				find[k].c[i]='1';
				i++;
			}
			else
			{
				printf("���ұ���ʱ����\n");
				break;
			}
			p=q;
			q=q->parents;
		}
		find[k].c[i]='\0';
		find[k].length=i-1;							//������ĳ��ȸ���find[k].length
		i=find[k].length;
		while(i>(find[k].length)/2)					//���ڱ����ǴӸ���㵽Ҷ�ӽ�㣬���Ե���˳��
		{
			
			find[k].c[0]=find[k].c[i];
			find[k].c[i]=find[k].c[find[k].length-i+1];
			find[k].c[find[k].length-i+1]=find[k].c[0];
			i--;
		}
	}
//	printf("��Find_Code�����н��в���:find[1].ch = %s ,find[1].c = %s",find[i].ch,find[i].c);
}

void Show_Code(code find[MAXSIZE],int j)
{
	int i,k,m=0;
	for(i=1;i<=j;i++)
	{
		printf("%s : %s \n",find[i].ch,find[i].c);
	}
}

void Read_Text(codetext *text)            //��ȡ�������ı����ַ���
{
	FILE *fp;
	int i=1;
	int h=0,j=0;
	char c;
	if((fp=fopen("C:\\Users\\Administrator\\Desktop\\�γ����\\�γ����������ı�\\��������ı�.txt","r"))==NULL)
	{
		printf("���ı�ʧ��\n�����Ϊ��");
		printf("%4d",ferror(fp));
		exit(0);
	}
	while(!feof(fp))					//ͳ�ƴ������ı���ռ���ֽ�����
	{
		c=fgetc(fp);
		h++;
	}
	h=h-1;
	rewind(fp);
	while(j<=h)
	{
			fgets(text->ch[i],3,fp);			//���ں����������ֽڱ�ʾ������ÿ�ζ�ȡǰ�����ֽڣ��������ֽ��Զ���'\0'
			j=j+2;
			if((text->ch[i][0]<0)&&(text->ch[i][1]<0))			//�����ڼ�����б�ʾΪ�����������ж��Ƿ�Ϊ���ֺ���ĸ�Լ�����
			{}
			else 
			{
				if(text->ch[i][0]=='\n')						//�س��ͻ��з��ڼ������ʾΪ�����ֽڣ����������ƶ��ļ�λ�ñ��
				{}
				else							//���˻��з����⣬������ĸ�������ڼ�����б�ʾΪһ���ֽڣ����������ƶ��ļ�λ�ñ��һ��
				{
					fseek(fp,-1,1);
					j=j-1;
				}
				text->ch[i][1]='\0';
			}
			i++;
	}
	i=i-2;
	text->length=i;
	fclose(fp);
}

int main()
{
	int j,i;
	code find[MAXSIZE];
	count *count_head = Init();
	linkhuf huf_head = Creat_Head() ,p;
	Statistics_Frequency(count_head);
	Write_Frequency(count_head);
	Read_Weight_Value(count_head,find,&j);
	Assingment(huf_head,find,j);
	printf("\n\n");
	Shelt_Sort(huf_head);
	Display(huf_head);	
	printf("\n\n\n\n****************************************************************************\n");
	huf_head->next = Creat_Huffman(huf_head->next);
	Pre_Order(huf_head->next);
	Find_Code(huf_head,find,j);
	Show_Code(find,j);
	return 0;
} 





























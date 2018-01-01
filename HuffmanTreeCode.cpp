#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAXSIZE 770
#define MAX 1000
#define FREQUENCY_FNAME "E:\\character_frequency.txt"

typedef struct node{
	int data;//Ȩֵ 
	struct node *lchild,*rchild,*parents,*next;
}hufnode;//Huffman���������

typedef hufnode* linkhuf;

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

typedef struct{
	linkhuf key[MAXSIZE];
	int length;
}recond; //����������ʱ�����ṹ��  


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
	while(p!=NULL && flag==1)	//���ж�ȡ�����ַ����ѽ������ַ�����ıȽϡ�
	{
		a=strcmp((p->info),c);
		if(a==0)
			flag=0;
		else
			p=p->next;
	}
	if(flag==0)	//���Ѵ��ڶ�ȡ�����ַ�������м�һ��
		p->num++;
	else 			//�������½�����㣬ͷ�巨���½ڵ���뵽��ǰ�� 
	{
		p=(count*)malloc(sizeof(count));//�����¿ռ� 
		strcpy(p->info,c);//���ַ����������ٵĿռ� 
		p->num=1;//�½ڵ���ִ���Ϊ1 
		p->next=head->next;
		head->next=p;//���½ڵ���뵽��һ���ڵ�λ�� 
	}
}

//ͳ���ı����ַ���Ƶ��
void Statistics_Frequency(count *head,char *fname)						
{
	FILE *fp;
	int i=0,j=0;
	char c[3];
	if((fp=fopen(fname,"r"))==NULL)
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
	rewind(fp);//���½��ļ�ָ���ƶ�����ǰ�� 
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
			else//���˻��з����⣬������ĸ�������ڼ�����б�ʾΪһ���ֽڣ����������ƶ��ļ�һ��λ�ñ��
			{
				//�˴�fsesk()�����ڶ���������ƫ������
				//��������ʾ���ļ������￪ʼƫ��,����ȡֵΪ��SEEK_CUR(ֵΪ0����ʾ�ļ���ͷλ��)�� SEEK_END(ֵΪ1����ʾ�ļ���ǰλ��) �� SEEK_SET(ֵΪ2����ʾ�ļ�ĩβλ��)
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
	char ch='\n';
	int i=0;
	if((fp=fopen(FREQUENCY_FNAME,"w"))==NULL)
	{
		printf("�ļ���ʧ��:\t");
		printf("%4d\n",ferror(fp));
		exit(0);
	}
	p=head->next;
	while(p!=NULL)
	{
		//���ڿո���ȥ���ȡʱ�ᱻ���ԣ��˴������� ASCii��ֵ32���棬
		//����32�������ַ���ɵ��ַ����������������ַ���ͻ��������붼������ ,�ѿո��ַ������ļ�ʱ��32���棬
		//���ļ���ȡʱҪ���ж����Ƿ��"32"��ȣ����������ÿո���� 
		if(strcmp(p->info," ")==0)
		{
			fputs("32",fp);
		}
		else
		{
			fputs(p->info,fp);	
		}
		fprintf(fp," %d  ",p->num);
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
	*j=*j-1;//���һ���ַ�Ϊ������ ��j-1 
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

//��ʼ�����������������,jΪ������ 
void Assingment(linkhuf head,code find[MAXSIZE],int j)				
{
	int i;
	linkhuf p = head,q;
	for(i=1;i<=j;i++)
	{
		q = (linkhuf)malloc(sizeof(hufnode));
		q->data = find[i].weight;
		q->lchild = NULL;
		q->rchild = NULL;
		q->parents = NULL;
		q->next = head->next;
		head->next = q;
		find[i].address = q;//��ÿһ�����ĵ�ַ��ֵ��find[i].address���Ա��ں����ҵ�ÿһ��Ҷ�ӽ��ı��롣
	}
}

/*
//���������ݰ�Ȩֵ��������  
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
	m.length = k-1;
	for(i=1;i<=m.length-1;i++)
	{
		for(j=i+1;j<=m.length;j++)
		{
			if(m.key[i]<m.key[j])
			{
				q = m.key[i];
				m.key[i] = m.key[j];
				m.key[j] = q;
			}
		}
	}
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
*/	
 
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
			while((j>0) && (m.key[0]->data < m.key[j]->data))//������Ƚ��Ҳ���λ�� 
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
		while(p1 && (s->data > p1->data))
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

//������������ĺ���
linkhuf Creat_Huffman(linkhuf root)						
{	
	linkhuf rl,rr,s,q;
	while(root && root->next)
	{
		q = root;
//		printf("\n=====================================================\n");
//      ��̬����Huffman��������� 
//		while(q)
//		{
//			printf("%d ",q->data);
//			q = q->next;
//		}
//		printf("\n=====================================================\n");
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
		find[k].length=i-1;	//������ĳ��ȸ���find[k].length
		i=find[k].length;
		while(i>(find[k].length)/2)	//���ڱ����ǴӸ���㵽Ҷ�ӽ�㣬���Ե���˳��
		{
			find[k].c[0]=find[k].c[i];
			find[k].c[i]=find[k].c[find[k].length-i+1];
			find[k].c[find[k].length-i+1]=find[k].c[0];
			i--;
		}
	}
}

//������� 
void Show_Code(code find[MAXSIZE],int j)
{
	int i,k,m=0;
	for(i=1;i<=j;i++)
	{
		printf("%s : %s \n",find[i].ch,find[i].c);
	}
}


//�����ļ� 
void encode_file()
{
	int j,i,k,menu_select;
	code find[MAXSIZE];
	count *count_head = Init();
	linkhuf huf_head = Creat_Head() ,p;
	char fname[200];
	printf("\n�������ļ�·��:");
	scanf("%s",fname);
	Statistics_Frequency(count_head,fname);//ͳ���ַ�Ƶ�� 
	Write_Frequency(count_head);//�洢�ַ�Ƶ�� 
	Read_Weight_Value(count_head,find,&j);//���ַ�Ƶ�ʴ���find���� 
	Assingment(huf_head,find,j);//��ʼ������ 
	Shelt_Sort(huf_head);//��Ȩֵ���� 
	huf_head->next = Creat_Huffman(huf_head->next);//����Huffman�� 
	Find_Code(huf_head->next,find,j);//���� 
	printf("\n����������:\n");
	Show_Code(find,j);//��������� 
} 


//�����ļ� 
void decode_file(code find[],int j)
{
	FILE *fp;
	char *s = (char*)malloc(sizeof(char)*20),c,flag=0,fname[30],text[2000]="\0";
	int i,k,n=0;
	printf("\n��������Ҫ������ļ�·��:");
	scanf("%s",fname);
	if((fp = fopen(fname,"r"))==NULL)
	{
		printf("�ļ���ʧ��");
		return;
	}
	k=0;
	while((c = fgetc(fp))!=EOF)
	{
		n++; 
		s[k++] = c;
		s[k]='\0';
		for(i=1;i<=j;i++)
		{
			if(strcmp(s,find[i].c)==0)
			{ 
				flag=1;
				if(strcmp(find[i].c,"32")==0)
				{
					strcat(text," ");
				}
				else
				{
					strcat(text,find[i].ch);	
				}
				break;
			}
		}
		if(flag==1)
		{
			flag=0;
			k=0;
			free(s);
			s = (char*)malloc(sizeof(char)*20);
		}
	}
	strcat(text,"\0");
	printf("\n���������Ϊ:\n");
	printf("%s\n",text);
} 

//�����ļ� 
void copy_file(char *source_file,char *dest_file)
{
	FILE *s ,*d;
	char c;
	if((s = fopen(source_file,"r"))==NULL)
	{
		printf("\nԴ�ļ���ʧ��\n");
		return;	
	} 
	if((d = fopen(dest_file,"w")) == NULL)
	{
		printf("\nĿ���ļ���ʧ��\n");
		return; 
	}
	while((c = fgetc(s))!=EOF)
	{
		fputc(c,d);
	}
	printf("\n�����ļ����\n");
	fclose(s);
	fclose(d);
}

void initCount(char *fname,count *count_head)
{
	FILE *fp;
	char s[3];
	int num;
	count *p,*q;
	p = count_head;
	if((fp=fopen(fname,"r")) ==NULL)
	{
		printf("\n�ļ���ʧ��\n");
		return;
	}
	while(fscanf(fp,"%s",s)!=EOF && fscanf(fp,"%d",&num)!=EOF)
	{
		q = (count*)malloc(sizeof(count));
		if(strcmp(s,"32")==0)
		{
			strcpy(q->info," ");
		}
		else
		{
			strcpy(q->info,s);	
		}
		q->num = num;
		q->next = p->next;
		p->next = q;	 
	}
	fclose(fp);
}
//����˵�
void menu()
{
	printf("\n*******************************�˵�*********************************\n\n\n");
	printf("\n1. ���ļ�����\n\n");
	printf("\n2. ���ļ�����\n\n");
	printf("\n3. �˳�\n\n");
	printf("\n��ѡ��:\t"); 
} 

int main()
{  
	int j=0,i,k,m,menu_select;
	code find[MAXSIZE];
	count *count_head = Init();
	linkhuf huf_head = Creat_Head() ,p;
	char fname[200];
	FILE *fp ;
	if((fp = fopen(FREQUENCY_FNAME,"r")) == NULL)
	{
		printf("\n��ʼ��Huffman��(ͨ�������ļ���ʼ��):");
		printf("\n�������ļ�·��:");
		scanf("%s",fname);
		Statistics_Frequency(count_head,fname);//ͳ���ַ�Ƶ�� 
		Write_Frequency(count_head);//�洢�ַ�Ƶ��  
		Read_Weight_Value(count_head,find,&j);//���ַ�Ƶ�ʴ���find���� 
		Assingment(huf_head,find,j);//��ʼ������ 
		Shelt_Sort(huf_head);//��Ȩֵ����
		huf_head->next = Creat_Huffman(huf_head->next);//����Huffman�� 
		Find_Code(huf_head->next,find,j);//����  
	}
	else
	{
		initCount(FREQUENCY_FNAME,count_head);
		Read_Weight_Value(count_head,find,&j);
		Assingment(huf_head,find,j);//��ʼ������ 
		Shelt_Sort(huf_head);//��Ȩֵ���� 
		huf_head->next = Creat_Huffman(huf_head->next);//����Huffman�� 
		Find_Code(huf_head->next,find,j);//����	
		printf("\nHuffman����ʼ������:\n\n"); 
		Show_Code(find,j);
	}
	system("pause");
	system("cls");
	menu();
	scanf("%d",&menu_select);
	if(menu_select!=5)
	{
		while(1)
		{	
			switch (menu_select)
			{
				case 1: 
					encode_file();
					system("pause");
					break;
				case 2:
					decode_file(find,j);
					system("pause");
					break;
				case 3:
					return 0;
				default:
					printf("\n������������������\n");
					system("pause");
					break; 
			}
			system("cls");
			menu();
			scanf("%d",&menu_select);
		}	
	}
	else
	{
		return 0;	
	}
} 





























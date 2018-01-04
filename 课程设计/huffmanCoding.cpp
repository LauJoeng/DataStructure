#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAXSIZE 770
#define MAX 1000
#define FREQUENCY_FNAME "E:\\character_frequency.txt"

typedef struct node{
	int data;
	struct node *lchild,*rchild,*parents,*next;
}hufnode;

typedef hufnode* linkhuf;

typedef struct code{
	char c[20];
	int weight;
	char ch[3];
	int length;
	linkhuf address;
}code;

typedef struct count{
	char info[3]; 
	int num; 
	struct count *next;
}count; 

typedef struct codetext{
	char ch[MAX][3];
	int length;
}codetext;

typedef struct{
	linkhuf key[MAXSIZE];
	int length;
}recond;

count* Init( )									
{
	count *head;
	head=(count*)malloc(sizeof(count));
	head->next=NULL;
	return (head);
}


void Statistics(char *c,count *head)
{
	int flag=1,a;
	count *p;
	p=head->next;
	while(p!=NULL && flag==1)
	{
		a=strcmp((p->info),c);
		if(a==0)
			flag=0;
		else
			p=p->next;
	}
	if(flag==0)
		p->num++;
	else  
	{
		p=(count*)malloc(sizeof(count)); 
		strcpy(p->info,c); 
		p->num=1; 
		p->next=head->next;
		head->next=p; 
	}
}

void Statistics_Frequency(count *head,char *fname)						
{
	FILE *fp;
	int i=0,j=0;
	char c[3];
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("文件打开失败\n");
		printf("%4d",ferror(fp));
		exit(0);
	}
	while(!feof(fp))
	{
		c[0]=fgetc(fp);
		i++;
	}
	i=i-1;
	rewind(fp); 
	while(j<i)											
	{
		fgets(c,3,fp);
		j=j+2;
		if(c[0]<0&&c[1]<0)
			Statistics(c,head);
		else 
		{
			if(c[0]=='\n')
			{
			
			}
			else
			{
				fseek(fp,-1,1);
				j=j-1;
			}
			c[1]='\0';
			Statistics(c,head);
		}
	}
	fclose(fp);
}

void Write_Frequency(count *head)   
{
	count *p;
	FILE *fp;
	char ch='\n';
	int i=0;
	if((fp=fopen(FREQUENCY_FNAME,"w"))==NULL)
	{
		printf("文件打开失败:\t");
		printf("%4d\n",ferror(fp));
		exit(0);
	}
	p=head->next;
	while(p!=NULL)
	{
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

void Read_Weight_Value(count *head,code *find,int *j)
{
	int i;
	count *p;
	p=head->next;
	while(p!=NULL)
	{
		strcpy(find[*j].ch,p->info);
		find[*j].weight=p->num;
		*j=*j+1;
		p=p->next;
	}
	*j=*j-1;
}

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
		find[i].address = q;
	}
}
 

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
		for(i=d+1;i<=m.length;i++)
		{
			m.key[0]=m.key[i];
			j=i-d; 
			while((j>0) && (m.key[0]->data < m.key[j]->data)) 
			{
				m.key[j+d]=m.key[j]; 
				j=j-d; 
			}
			m.key[j+d]=m.key[0];
		}
		d=d/2;
	}while(d>=1);
	head->next=m.key[1];
	q=head->next;
	i=2;
	p=m.key[i];
	while(i<=m.length)
	{
		q->next=p;
		q=q->next;
		p=m.key[i];
		i++;
	}
	q->next=p;
	q->next->next=NULL;
}

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

linkhuf Creat_Huffman(linkhuf root)						
{	
	linkhuf rl,rr,s,q;
	while(root && root->next)
	{
		q = root;
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

void Find_Code(linkhuf head,code find[MAXSIZE],int j)
{
	int weight;
	int i,k;
	linkhuf p,q;
	for(k=1;k<=j;k++)
	{
		weight=find[k].weight;									
		p=find[k].address;
		q=p->parents;
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
				printf("编码出错\n");
				break;
			}
			p=q;
			q=q->parents;
		}
		find[k].c[i]='\0';
		find[k].length=i-1;	
		i=find[k].length;
		while(i>(find[k].length)/2)
		{
			find[k].c[0]=find[k].c[i];
			find[k].c[i]=find[k].c[find[k].length-i+1];
			find[k].c[find[k].length-i+1]=find[k].c[0];
			i--;
		}
	}
}

void Show_Code(code find[MAXSIZE],int j)
{
	int i,k,m=0;
	for(i=1;i<=j;i++)
	{
		printf("%s : %s \n",find[i].ch,find[i].c);
	}
}

 
void encode_file()
{
	int j,i,k,menu_select;
	code find[MAXSIZE];
	count *count_head = Init();
	linkhuf huf_head = Creat_Head() ,p;
	char fname[200];
	printf("\n请输入需要编码的文件路径:");
	scanf("%s",fname);
	Statistics_Frequency(count_head,fname);
	//Write_Frequency(count_head);
	Read_Weight_Value(count_head,find,&j); 
	Assingment(huf_head,find,j); 
	Shelt_Sort(huf_head); 
	huf_head->next = Creat_Huffman(huf_head->next); 
	Find_Code(huf_head->next,find,j);
	printf("\n编码结果如下:\n");
	Show_Code(find,j);
} 
 
void decode_file(code find[],int j)
{
	FILE *fp;
	char *s = (char*)malloc(sizeof(char)*20),c,flag=0,fname[30],text[2000]="\0";
	int i,k,n=0;
	printf("\n请输入需要解码的文件路径:");
	scanf("%s",fname);
	if((fp = fopen(fname,"r"))==NULL)
	{
		printf("\n文件打开失败\n");
		return;
	}
	k=0;
	while((c = fgetc(fp))!=EOF)
	{
		n++; 
		if(c=='0' || c=='1')
		{
			s[k++] = c;	
		}
		else
		{
			continue;
		}
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
	printf("\n解码内容如下:\n");
	printf("%s\n",text);
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
		printf("\n文件打开失败\n");
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

create_sourcefile(code find[],int j)
{
	FILE *efile,*dfile;
	char c;
	int i;
	efile = fopen("E://English_encode_test_file.txt","r");
	dfile = fopen("E://test.txt","w");
	while((c=fgetc(efile))!=EOF)
	{
		printf("\n读取到字符%c\n",c);
		for(i=1;i<=j;i++)
		{
			printf("c=%c , find[i].ch[0]= %c\n",c,find[i].ch[0]);
			if(find[i].ch[0]==c||c==' ')
			{
				if(c==' ')
				{
					fputs("001",dfile);
				}
				else
				{
					fputs(find[i].c,dfile);
				}
				break;
			}
		}
	}
}

void menu()
{
	printf("\n*******************************菜单*********************************\n\n\n");
	printf("\n1. 编码文件\n");
	printf("\n2. 解码文件\n");
	printf("\n3. 退出\n");
	printf("\n请选择:\t"); 
} 

int main()
{  
	int j=1,i,k,m,menu_select;
	code find[MAXSIZE];
	count *count_head = Init();
	linkhuf huf_head = Creat_Head() ,p;
	char fname[200];
	FILE *fp ;
	if((fp = fopen(FREQUENCY_FNAME,"r")) == NULL)
	{
		printf("\n初始化Huffman树\n");
		printf("\n(将通过编码文件初始化)请输入文件路径:");
		scanf("%s",fname);
		Statistics_Frequency(count_head,fname);
		Write_Frequency(count_head);
		Read_Weight_Value(count_head,find,&j); 
		Assingment(huf_head,find,j); 
		Shelt_Sort(huf_head);
		huf_head->next = Creat_Huffman(huf_head->next); 
		Find_Code(huf_head->next,find,j);  
	}
	else
	{
		initCount(FREQUENCY_FNAME,count_head);
		Read_Weight_Value(count_head,find,&j);
		Assingment(huf_head,find,j); 
		Shelt_Sort(huf_head); 
		huf_head->next = Creat_Huffman(huf_head->next); 
		Find_Code(huf_head->next,find,j);
		printf("\nHuffman树初始化结果如下:\n\n"); 
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
					printf("\n输入有误,请重新进入\n");
					return 0; 
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




























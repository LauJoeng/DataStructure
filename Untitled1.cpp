#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAXSIZE 770
#define MAX 1000
typedef struct node{
	int data;//权值 
	struct node *lchild,*rchild,*parents,*next;
}hufnode;//Huffman树结点类型
 
typedef hufnode* linkhuf;

typedef struct{
	linkhuf key[MAXSIZE];
	int length;
}recond; //进行shell排序临时辅助结构体 

typedef struct code{
	char c[20];//存储编码 
	int weight;//权值 
	char ch[3];//字符 
	int length;//编码长度 
	linkhuf address;//存储每个结点地址，以便找到每一个叶子结点的编码 
}code;

typedef struct count{
	char info[3];	//存储字节，因为可能存在汉字，因此采用字符串存储 
	int num;		//该字节出现频率 
	struct count *next;
}count;//统计字符频率链表结点类型 

typedef struct codetext{
	char ch[MAX][3];
	int length;
}codetext;//存储文本字符结点类型 


//建立统计字符频率的链表的头结点
count* Init( )									
{
	count *head;
	head=(count*)malloc(sizeof(count));
	head->next=NULL;
	return (head);
}

//统计字符频率 
void Statistics(char *c,count *head)
{
	int flag=1,a;
	count *p;
	p=head->next;
	while(p!=NULL&&flag==1)	//进行读取到的字符和已建立的字符链表的比较。
	{
		a=strcmp((p->info),c);
		if(a==0)
			flag=0;
		else
			p=p->next;
	}
	if(flag==0)		//若已存在读取到的字符，则进行加一。
		p->num++;
	else 			//否则重新建立结点
	{
		p=(count*)malloc(sizeof(count));
		strcpy(p->info,c);
		p->num=1;
		p->next=head->next;
		head->next=p;//将新节点插入到第一个节点位置 
	}
}

//统计文本中字符的频率
void Statistics_Frequency(count *head)						
{
	FILE *fp;
	int i=0,j=0;
	char c[3];
	if((fp=fopen("E:\\code\\testfile.txt","r"))==NULL)
	{
		printf("打开文件失败\n");
		printf("%4d",ferror(fp));
		exit(0);
	}
	while(!feof(fp)) //统计待处理文本的字节数
	{
		c[0]=fgetc(fp);
		i++;
	}
	i=i-1;
	rewind(fp);
	while(j<i)											
	{
		fgets(c,3,fp);		//由于汉字用两个字节表示，所以每次读取前两个字节，第三个字节自动加'\0'
		j=j+2;
		if(c[0]<0&&c[1]<0)	//汉字在计算机中表示为负数，所以判断是否为汉字和字母以及数字
			Statistics(c,head);
		else 
		{
			if(c[0]=='\n')	//回车和换行符在计算机表示为两个字节，所以无需移动文件位置标记
			{
			
			}
			else//除了换行符以外，其它字母和数字在计算机中表示为一个字节，所以向右移动文件位置标记一个
			{
				fseek(fp,-1,1);
				j=j-1;
			}
			c[1]='\0';
			Statistics(c,head);	//比较读取到的字符是否在已建立的字符链表中
		}
	}
	fclose(fp);
}

//把统计的字符的频率写进文本中
void Write_Frequency(count *head)   
{
	count *p;
	FILE *fp;
	char c[20]="的字符频率为：",ch='\n';
	int i=0;
	if((fp=fopen("E:\\code\\characater_frequency.txt","w"))==NULL)
	{
		printf("该文本的各个字符的频率.txt打开失败\n");
		printf("失败的原因\n");
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

//把字符的频率写进到find[maxisize].weight中,指针j接收字符个数 
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
	*j=*j-1;//最后一个字符为结束符 
}

//初始化Huffman树 
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

//开始构造哈弗曼树的链表
void Assingment(linkhuf head,code find[MAXSIZE],int j)				
{
	int i;
	linkhuf p = head,q;
	for(i=1;i<=j;i++)
	{
//		Append(p,find[i].weight);
//		find[i].address=head->next;	//把每一个结点的地址赋值给find[i].address，以便于后续找到每一个叶子结点的编码。
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

//对链表数据按权值进行shell排序 
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
		for(i=d+1;i<=m.length;i++)//从第d+1个元素开始，将所有元素有序插入对应分组中 
		{
			m.key[0]=m.key[i];//保存第i个元素 
			j=i-d;//向前找插入位置 
			while(j>0&&m.key[0]->data<m.key[j]->data)//排序码比较找插入位置 
			{
				m.key[j+d]=m.key[j];//记录后移 
				j=j-d;//继续向前查找 
			}
			m.key[j+d]=m.key[0];//插入第i个元素的副本 
		}
		d=d/2;
	}while(d>=1);
	head->next=m.key[1];	//将排好序的结点的第一个地址赋给头结点的next。
	q=head->next;	//将第一个结点的地址赋给q。
	i=2;
	p=m.key[i];
	while(i<=m.length)	//将已排好序的地址赋给后续的next。
	{
		q->next=p;
		q=q->next;
		p=m.key[i];
		i++;
	}
	q->next=p;
	q->next->next=NULL;
}

//输出已排序好的权值
void Display(linkhuf head)								
{
	linkhuf p;
	p=head->next;
	printf("已进行排序的权值如下:\n");
	while(p!=NULL)
	{
		printf("%4d",p->data);
		p=p->next;
	}
}

//构造哈夫曼树所需的插入函数
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

//构造哈弗曼的函数
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

//前序遍历哈夫曼树
void Pre_Order(linkhuf head)									
{
	if(head!=NULL)
	{
		printf("%4d\n",head->data);
		Pre_Order(head->lchild);
		Pre_Order(head->rchild);
	}
}

//进行哈夫曼编码，存储在find[maxsize].c中
void Find_Code(linkhuf head,code find[MAXSIZE],int j)
{
	int weight;
	int i,k;
	linkhuf p,q;
	for(k=1;k<=j;k++)
	{
		weight=find[k].weight;									
		p=find[k].address;	//由于find[k].address存储有叶子结点的地址，
		q=p->parents;	//根据父母亲的结点依次找到根结点。
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
				printf("查找编码时出错\n");
				break;
			}
			p=q;
			q=q->parents;
		}
		find[k].c[i]='\0';
		find[k].length=i-1;							//将编码的长度赋给find[k].length
		i=find[k].length;
		while(i>(find[k].length)/2)					//由于编码是从根结点到叶子结点，所以调换顺序；
		{
			
			find[k].c[0]=find[k].c[i];
			find[k].c[i]=find[k].c[find[k].length-i+1];
			find[k].c[find[k].length-i+1]=find[k].c[0];
			i--;
		}
	}
//	printf("在Find_Code函数中进行测试:find[1].ch = %s ,find[1].c = %s",find[i].ch,find[i].c);
}

void Show_Code(code find[MAXSIZE],int j)
{
	int i,k,m=0;
	for(i=1;i<=j;i++)
	{
		printf("%s : %s \n",find[i].ch,find[i].c);
	}
}

void Read_Text(codetext *text)            //读取待处理文本的字符。
{
	FILE *fp;
	int i=1;
	int h=0,j=0;
	char c;
	if((fp=fopen("C:\\Users\\Administrator\\Desktop\\课程设计\\课程设计所需的文本\\待处理的文本.txt","r"))==NULL)
	{
		printf("打开文本失败\n错误号为：");
		printf("%4d",ferror(fp));
		exit(0);
	}
	while(!feof(fp))					//统计待处理文本所占的字节数。
	{
		c=fgetc(fp);
		h++;
	}
	h=h-1;
	rewind(fp);
	while(j<=h)
	{
			fgets(text->ch[i],3,fp);			//由于汉字用两个字节表示，所以每次读取前两个字节，第三个字节自动加'\0'
			j=j+2;
			if((text->ch[i][0]<0)&&(text->ch[i][1]<0))			//汉字在计算机中表示为负数，所以判断是否为汉字和字母以及数字
			{}
			else 
			{
				if(text->ch[i][0]=='\n')						//回车和换行符在计算机表示为两个字节，所以无需移动文件位置标记
				{}
				else							//除了换行符以外，其它字母和数字在计算机中表示为一个字节，所以向右移动文件位置标记一个
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





























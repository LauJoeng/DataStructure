#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define MAX  100
#define FILENAME "E:\\hfmTree.txt"

typedef char **HuffmanCode;//动态创建数组存储Huffman码表
typedef struct
{
	int weight;//权值 
	int parent,lchild,rchild; 
} HuffmanTree;//Huffman树节点类型 

typedef struct
{
	HuffmanTree* HT;//Huffman树节点 
	char *c;//待编码字符串 
	int length;//字符个数 
	HuffmanCode HC;//存储Huffman编码的数组； 
}Huffman;

Huffman hfm;
char k;


/*
*选择Huffman树中无双亲且权值最小的两个节点，它们的下标分别传给a和b	
*/
void select(HuffmanTree* HT,int end,int *a,int *b)
{
	int  i;
	int min1 = 99999;
	int min2 = 99999;
	//第一趟循环查找最小权值的下标 
	for(i = 1;i < end;i++)
	{
		if(HT[i].parent == 0&&HT[i].weight<min1)
		{
			*a = i;
			min1 = HT[i].weight;
		}
	}
	//第二趟循环查找第二小权值的下标 
	for(i = 1;i <= end;i++)
	{
		if(HT[i].parent == 0 && HT[i].weight<min2 && (i!=*a))
		{
			*b = i;
			min2 = HT[i].weight;
		}
	}
}

//构建Huffman树，并求Huffman编码 
Huffman HuffmanCoding(Huffman hfm)
{
	int i,n,m,a,b,start;
	int c,f;
	char *cd;//求编码临时字符串 
	n = hfm.length;//n为需要编码的字符个数 
	if(n<=1)
	{
		return hfm;//若编码字符个数小于1则直接返回 
	}
	m=2*n-1;//若编码字符大于1，则生成的Huffman树总结点个数为2*n-1
	for(i = n+1;i < m;i++)
	{
		select(hfm.HT,i-1,&a,&b);
		//修改父亲位置 
		hfm.HT[a].parent = i;
		hfm.HT[b].parent = i;
		//修改父亲孩子节点位置 
		hfm.HT[i].lchild = a;
		hfm.HT[i].rchild = b; 
		
		hfm.HT[i].weight = hfm.HT[a].weight + hfm.HT[b].weight;//将左右孩子节点权值之和赋给父亲

		hfm.HC = (HuffmanCode)malloc((n+1)*sizeof(char*)); //分配n个字符编码的头指针
		cd = (char*)malloc(n*sizeof(char)); //分配求编码的空间
		cd[n-1] = '\0';//编码最后一个字符为结束符
		
		for(i = 1;i <= n;i++)
		{
			start = n-1;//确定编码最后一个位置，后逐步向前移动 
			for(c = i,f = hfm.HT[i].parent;f!=0;c = f,f = hfm.HT[f].parent)//从叶子结点逆向求编码 
			{
				if(c == hfm.HT[i].lchild)
				{ 
					cd[--start] = '0';//规定从上到下走向左孩子为0 
				}
				else
				{
					cd[--start] = '1';//右孩子为1 
				}
			}
			hfm.HC[i] = (char*)malloc((n-start)*sizeof(char));//该字符编码的长度 
			strcpy(hfm.HC[i],&cd[start]);//从cd复制编码到hfm.HC 
		}
	}
	free(cd);
	return hfm; 
}

//从文件读取Huffman结构体文件 
Huffman readHfmObject(char *fname)
{
	FILE *fp;
	if((fp = fopen(*fname)) == NULL)
	{
		printf("\n读取文件失败!\n");
		return NULL;
	}
	else
	{
		
	}
}

//将Huffman结构体写入文件 
void writeHuffmanObject(Huffman hfm)
{
	
}

//保存用户将要编码的字符和权值到文件 
Huffman inputHuffman(Huffman hfm)
{
	int i,n = 0;
	FILE *fp; 
	printf("\n***********************************初始化****************************************\n");
	printf("\n\n字符和权重将保存到文件:E:\\hfmtree.txt\n\n");
	while(1)
	{
		printf("请输入要编码的字符个数(大于1):");
		scanf("%d",&n);
		if(n > 1)
		{
			break;
		}
	}
	hfm.HT = (HuffmanTree*)malloc((2*n)*sizeof(HuffmanTree));
	hfm.c = (char*)malloc((n+1)*sizeof(char));
	//初始化原始字符存储空间 
	for(i = 1;i <=n;i++)
	{
		printf("\n请输入第%d个字符:",i);
		scanf("%s",&hfm.c[i]);
		printf("\n请输入第%d个字符的权值:",i);
		scanf("%d",&hfm.HT[i].weight);
		hfm.HT[i].lchild = 0;
		hfm.HT[i].rchild = 0;
		hfm.HT[i].parent = 0;
	}
	//初始化原始字符节点以外的空间
	for(;i < 2*n-1;i++)
	{
		hfm.HT[i].lchild = 0;
		hfm.HT[i].rchild = 0;
		hfm.HT[i].parent = 0;
		hfm.HT[i].weight = 0;	
	} 
	hfm.length = n;//将长度值赋给Huffman树结构体
	if((fp = fopen(FILENAME,"w+")) == NULL)
	{
		printf("\n打开文件失败!\n");
		return hfm; 
	}
	if((fwrite(&hfm,sizeof(HuffmanTree),1,fp)) == 1)
	{
		printf("\n数据以保存!\n");
		rewind(fp);
	}
	else
	{
		printf("\n数据保存失败!\n");
	}
	return hfm;
}


Huffman initHuffman(Huffman hfm)
{
	int n,i,x = -1;
	FILE *fp;
	if((fp = fopen(FILENAME,"rt")) == NULL)//对文件一读文本的形式打开
	{
		hfm = inputHuffman(hfm);
	}
	else
	{
		printf("\nHuffman树已经初始化过，是否重新初始化(是:1   否:0)?  ");
		while(1)
		{
			printf("请正确选择:\n");
			scanf("%d",&x);
			if(x == 1 || x == 0)
			{
				break;
			}
		}
		if(x == 1)
		{
			hfm = inputHuffman(hfm);	
		}
		else
		{
			hfm = readHfmObject(FILENAME);
		}
	}
}



int main()
{
	return 0;
}	












































































#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define MAX  100
#define FILENAME "E:\\hfmTree.txt"

typedef char **HuffmanCode;//��̬��������洢Huffman���
typedef struct
{
	int weight;//Ȩֵ 
	int parent,lchild,rchild; 
} HuffmanTree;//Huffman���ڵ����� 

typedef struct
{
	HuffmanTree* HT;//Huffman���ڵ� 
	char *c;//�������ַ��� 
	int length;//�ַ����� 
	HuffmanCode HC;//�洢Huffman���������
}Huffman;

Huffman hfm;
char k;


/*
*ѡ��Huffman������˫����Ȩֵ��С�������ڵ㣬���ǵ��±�ֱ𴫸�a��b	
*/
void select(HuffmanTree* HT,int end,int *a,int *b)
{
	int  i;
	int min1 = 99999;
	int min2 = 99999;
	//��һ��ѭ��������СȨֵ���±� 
	for(i = 1;i < end;i++)
	{
		if(HT[i].parent == 0&&HT[i].weight<min1)
		{
			*a = i;
			min1 = HT[i].weight;
		}
	}
	//�ڶ���ѭ�����ҵڶ�СȨֵ���±� 
	for(i = 1;i <= end;i++)
	{
		if(HT[i].parent == 0 && HT[i].weight<min2 && (i!=*a))
		{
			*b = i;
			min2 = HT[i].weight;
		}
	}
}

//����Huffman��������Huffman���� 
Huffman HuffmanCoding(Huffman hfm)
{
	int i,n,m,a,b,start,k;
	int c,f;
	char *cd;//�������ʱ�ַ��� 
	n = hfm.length;//nΪ��Ҫ������ַ����� 
	if(n<=1)
	{
		return hfm;//�������ַ�����С��1��ֱ�ӷ��� 
	}
	m=2*n-1;//�������ַ�����1�������ɵ�Huffman���ܽ�����Ϊ2*n-1
	for(i = n+1;i <= m;i++)
	{
		select(hfm.HT,i-1,&a,&b);
		//�޸ĸ���λ�� 
		hfm.HT[a].parent = i;
		hfm.HT[b].parent = i;
		//�޸ĸ��׺��ӽڵ�λ�� 
		hfm.HT[i].lchild = a;
		hfm.HT[i].rchild = b; 
		
		hfm.HT[i].weight = hfm.HT[a].weight + hfm.HT[b].weight;//�����Һ��ӽڵ�Ȩֵ֮�͸�������
	}
	
//	for(i = 1;i <= m;i++)
//	{
//		printf("%d: lchild is :%d ,rchild is: %d,weight is %d\n",i,hfm.HT[i].lchild,hfm.HT[i].rchild,hfm.HT[i].weight);
//	}

	hfm.HC = (HuffmanCode)malloc((n+1)*sizeof(char*)); //����n���ַ������ͷָ��
	cd = (char*)malloc((m+1)*sizeof(char)); //���������Ŀռ�
	cd[m] = '\0';//�������һ���ַ�Ϊ������
	
	for(i = 1;i <= n;i++)
	{
		start = m;//ȷ���������һ��λ�ã�������ǰ�ƶ� 
		for(c = i,f = hfm.HT[i].parent;f!=0;c = f,f = hfm.HT[f].parent)//��Ҷ�ӽ����������� 
		{
//			printf("\nhfm.HT[%d].parent = %d,hfm.HT[%d].lchild = %d\n",c,hfm.HT[c].parent,f,hfm.HT[f].lchild);
//			printf("c = %d,f = %d\n",c,f);
			if(c == hfm.HT[f].lchild)
			{ 
				cd[--start] = '0';//�涨���ϵ�����������Ϊ0 
			}
			else if(c == hfm.HT[f].rchild) 
			{
				cd[--start] = '1';//�Һ���Ϊ1 
			}
//			printf("c = %d,f = %d   cd[%d] = %c \n",c,f,start,cd[start]);
		}
		hfm.HC[i] = (char*)malloc((m+1-start)*sizeof(char));//���ַ�����ĳ���
		strcpy(hfm.HC[i],&cd[start]);//��cd���Ʊ��뵽hfm.HC 
	}
	free(cd);
//	for(i = 1;i <= hfm.length;i++)
//	{
//		printf("%c : %s \n",hfm.c[i],hfm.HC[i]);
//	}
	return hfm; 
}

//���ļ���ȡHuffman�ṹ���ļ� 
 void readHfmObject(Huffman &hfm,char *fname)
{ 
	int i;
	FILE *fp;
	if((fp = fopen(fname,"r")) == NULL)
	{
		printf("\n��ȡ�ļ�ʧ��!\n");
		return;
	}
	else
	{
		fscanf(fp,"%d",&hfm.length);
		for(i = 1; i <= hfm.length;i++)
		{
			fscanf(fp," %c %d ",&hfm.c[i],&hfm.HT[i].weight);
		}
	}
	rewind(fp);
}

//��Huffman�ṹ��д���ļ� 
void writeHuffmanObject(Huffman hfm,char *fname)
{
	int i;
	FILE *fp;
	fp = fopen(fname,"w+");
	fprintf(fp,"%d\n",hfm.length);
	for(i = 1;i <= hfm.length;i++)
	{
		fprintf(fp,"%c %d ",hfm.c[i],hfm.HT[i].weight);
	}
	rewind(fp);
}

//�����û���Ҫ������ַ���Ȩֵ���ļ� 
Huffman inputHuffman(Huffman hfm)
{
	int i,n = 0;
	FILE *fp; 
	printf("\n***********************************��ʼ��****************************************\n");
	printf("\n\n�ַ���Ȩ�ؽ����浽�ļ�:E:\\hfmtree.txt\n\n");
	while(1)
	{
		printf("������Ҫ������ַ�����(����1):");
		scanf("%d",&n);
		if(n > 1)
		{
			break;
		}
	}
	hfm.HT = (HuffmanTree*)malloc((2*n)*sizeof(HuffmanTree));
	hfm.c = (char*)malloc((n+1)*sizeof(char));
	//��ʼ��ԭʼ�ַ��洢�ռ� 
	for(i = 1;i <=n;i++)
	{
		printf("\n�������%d���ַ�:",i);
		getchar();
		scanf("%c",&hfm.c[i]);
		printf("\n�������%d���ַ���Ȩֵ:",i);
		scanf("%d",&hfm.HT[i].weight);
		hfm.HT[i].lchild = 0;
		hfm.HT[i].rchild = 0;
		hfm.HT[i].parent = 0;
	}
	//��ʼ��ԭʼ�ַ��ڵ�����Ŀռ�
	for(;i <= 2*n-1;i++)
	{
		hfm.HT[i].lchild = 0;
		hfm.HT[i].rchild = 0;
		hfm.HT[i].parent = 0;
		hfm.HT[i].weight = 0;	
	} 
	hfm.length = n;//������ֵ����Huffman���ṹ��
	return hfm;
}


Huffman initHuffman(Huffman hfm)
{
	int n,i,x ;
	FILE *fp;
	fp = fopen(FILENAME,"rt");
	if(fp == NULL)//���ļ�һ���ı�����ʽ��
	{
		hfm = inputHuffman(hfm);
//		fp = fopen(FILENAME,"wt");
//		fprintf(fp,"%d\n",hfm.length);
//		for(i = 1;i <= hfm.length;i++)
//		{
//			fprintf(fp,"%c %d ",hfm.c[i],hfm.HT[i].weight);
//		}
//		rewind(fp);
		writeHuffmanObject(hfm,FILENAME);
	}
	else
	{
		printf("\nHuffman���Ѿ���ʼ�������Ƿ����³�ʼ��?(��:1   ��:0)  ");
		while(1)
		{
			printf("����ȷѡ��:\n");
			scanf("%d",&x);
			if(x == 1 || x == 0)
			{
				break;
			}
		}
		if(x == 1)
		{
			hfm = inputHuffman(hfm);
//			fp = fopen(FILENAME,"w+");
//			fprintf(fp,"%d\n",hfm.length);
//			for(i = 1;i <= hfm.length;i++)
//			{
//				fprintf(fp,"%c %d ",hfm.c[i],hfm.HT[i].weight);	
//			}
//			rewind(fp);
			writeHuffmanObject(hfm,FILENAME);
		}
		else
		{
			fscanf(fp,"%d",&n);
			hfm.c = (char*)malloc((n+1)*sizeof(char));
			hfm.HT = (HuffmanTree*)malloc((2*n)*sizeof(HuffmanTree));
			for(i = 1;i <= n;i++)
			{
				fscanf(fp," %c %d ",&hfm.c[i],&hfm.HT[i].weight);//���Ѿ����ļ��е��ַ������Ӧ��Ȩ�����뵽hfm.c[i]��hfm.HT[i].weight
			}
			for(i = 1;i <= n;i++)
			{
				hfm.HT[i].parent = 0;
				hfm.HT[i].lchild = 0;
				hfm.HT[i].rchild = 0;
			}
			for(;i <= 2*n-1;i++)
			{
				hfm.HT[i].parent = 0;
				hfm.HT[i].lchild = 0;
				hfm.HT[i].rchild = 0;
				hfm.HT[i].weight = 0;
			}
			hfm.length = n;
		}
	}
	fclose(fp);
	hfm = HuffmanCoding(hfm);
	return hfm;
}

int main()
{
	int i =0;
	
	hfm = initHuffman(hfm);
//	for(i = 1;i <= 2*hfm.length-1;i++)
//	{
//		printf("%d: parent is %d,lchild is :%d ,rchild is: %d,weight is %d\n",i,hfm.HT[i].lchild,hfm.HT[i].rchild,hfm.HT[i].weight);
//	}
	printf("\n����������:\n");
	for(i = 1;i <= hfm.length;i++)
	{
		printf("%c: %s\n",hfm.c[i],hfm.HC[i]);
	}
	 
	return 0;
}	












































































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
	HuffmanCode HC;//�洢Huffman��������飻 
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
	int i,n,m,a,b,start;
	int c,f;
	char *cd;//�������ʱ�ַ��� 
	n = hfm.length;//nΪ��Ҫ������ַ����� 
	if(n<=1)
	{
		return hfm;//�������ַ�����С��1��ֱ�ӷ��� 
	}
	m=2*n-1;//�������ַ�����1�������ɵ�Huffman���ܽ�����Ϊ2*n-1
	for(i = n+1;i < m;i++)
	{
		select(hfm.HT,i-1,&a,&b);
		//�޸ĸ���λ�� 
		hfm.HT[a].parent = i;
		hfm.HT[b].parent = i;
		//�޸ĸ��׺��ӽڵ�λ�� 
		hfm.HT[i].lchild = a;
		hfm.HT[i].rchild = b; 
		
		hfm.HT[i].weight = hfm.HT[a].weight + hfm.HT[b].weight;//�����Һ��ӽڵ�Ȩֵ֮�͸�������

		hfm.HC = (HuffmanCode)malloc((n+1)*sizeof(char*)); //����n���ַ������ͷָ��
		cd = (char*)malloc(n*sizeof(char)); //���������Ŀռ�
		cd[n-1] = '\0';//�������һ���ַ�Ϊ������
		
		for(i = 1;i <= n;i++)
		{
			start = n-1;//ȷ���������һ��λ�ã�������ǰ�ƶ� 
			for(c = i,f = hfm.HT[i].parent;f!=0;c = f,f = hfm.HT[f].parent)//��Ҷ�ӽ����������� 
			{
				if(c == hfm.HT[i].lchild)
				{ 
					cd[--start] = '0';//�涨���ϵ�����������Ϊ0 
				}
				else
				{
					cd[--start] = '1';//�Һ���Ϊ1 
				}
			}
			hfm.HC[i] = (char*)malloc((n-start)*sizeof(char));//���ַ�����ĳ��� 
			strcpy(hfm.HC[i],&cd[start]);//��cd���Ʊ��뵽hfm.HC 
		}
	}
	free(cd);
	return hfm; 
}

//���ļ���ȡHuffman�ṹ���ļ� 
Huffman readHfmObject(char *fname)
{
	FILE *fp;
	if((fp = fopen(*fname)) == NULL)
	{
		printf("\n��ȡ�ļ�ʧ��!\n");
		return NULL;
	}
	else
	{
		
	}
}

//��Huffman�ṹ��д���ļ� 
void writeHuffmanObject(Huffman hfm)
{
	
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
		scanf("%s",&hfm.c[i]);
		printf("\n�������%d���ַ���Ȩֵ:",i);
		scanf("%d",&hfm.HT[i].weight);
		hfm.HT[i].lchild = 0;
		hfm.HT[i].rchild = 0;
		hfm.HT[i].parent = 0;
	}
	//��ʼ��ԭʼ�ַ��ڵ�����Ŀռ�
	for(;i < 2*n-1;i++)
	{
		hfm.HT[i].lchild = 0;
		hfm.HT[i].rchild = 0;
		hfm.HT[i].parent = 0;
		hfm.HT[i].weight = 0;	
	} 
	hfm.length = n;//������ֵ����Huffman���ṹ��
	if((fp = fopen(FILENAME,"w+")) == NULL)
	{
		printf("\n���ļ�ʧ��!\n");
		return hfm; 
	}
	if((fwrite(&hfm,sizeof(HuffmanTree),1,fp)) == 1)
	{
		printf("\n�����Ա���!\n");
		rewind(fp);
	}
	else
	{
		printf("\n���ݱ���ʧ��!\n");
	}
	return hfm;
}


Huffman initHuffman(Huffman hfm)
{
	int n,i,x = -1;
	FILE *fp;
	if((fp = fopen(FILENAME,"rt")) == NULL)//���ļ�һ���ı�����ʽ��
	{
		hfm = inputHuffman(hfm);
	}
	else
	{
		printf("\nHuffman���Ѿ���ʼ�������Ƿ����³�ʼ��(��:1   ��:0)?  ");
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












































































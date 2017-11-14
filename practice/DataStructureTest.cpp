#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include <windows.h>

#define SWN 3
#define NAMELEN 20
#define CODELEN 10
#define FNAMELEN 80
#define BUFLEN 80
#define HOMELEN 15
#define SEXLEN 7
#define BIRTHLEN 9
#define PHONELEN 12

char schoolworks[SWN][NAMELEN+1]={"DataStructure","Mathmatic","English"};

struct record
{
	char name[NAMELEN+1];
	char code[CODELEN+1];
	char sex[SEXLEN+1];
	char birth[BIRTHLEN+1];
	char cellphone[PHONELEN+1];
	char hometown[HOMELEN+1];
	int marks[SWN];
	int total;
	struct record *next; 
}stu;

struct record *head;


int total[SWN];
FILE *stfpt;
char stuf[FNAMELEN];

int xuefen[3]={3,5,4};
float jidian[SWN];

void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void write_record(FILE *fp,struct record *rpt)
{
	int i;
	fprintf(fp,"%s\n",rpt->name);
	fprintf(fp,"%s\n",rpt->code);
	fprintf(fp,"%s\n",rpt->sex);
	fprintf(fp,"%s\n",rpt->birth);
	fprintf(fp,"%s\n",rpt->hometown);
	fprintf(fp,"%s\n",rpt->cellphone);
	for(i=0;i<SWN;i++)
	{
		fprintf(fp,"%d\n",rpt->marks[i]);
	}
}

int read_record(FILE *fp,struct record *rc)
{
	char buf[BUFLEN];
	int i;
	if(fscanf(fp,"%s",buf)!=1)
	{
		return 0;
	}
	strncpy(rc->name,buf,NAMELEN);
	fscanf(fp,"%s",buf);
	strncpy(rc->code,buf,CODELEN);
	fscanf(fp,"%s",buf);
	strncpy(rc->sex,buf,SEXLEN);
	fscanf(fp,"%s",buf);
	strncpy(rc->birth,buf,BIRTHLEN);
	fscanf(fp,"%s",buf);
	strncpy(rc->hometown,buf,HOMELEN);
	fscanf(fp,"%s",buf);
	strncpy(rc->cellphone,buf,PHONELEN);
	for(i = 0; i < SWN;i++)
	{
		fscanf(fp,"%d",&rc->marks[i]);
	}
	for(rc->total=0,i=0;i<SWN;i++)
	{
		rc->total+=rc->marks[i];
	}
	return 1;
} 

void displaystu(struct record stu)
{
	int i;
	printf("***********************");
	printf("\nName:%s\n",stu.name);
	printf("Code:%s\n",stu.code);
	printf("Sex:%s\n",stu.sex);
	printf("Birth:%s\n",stu.birth);
	printf("Cellphone:%s\n",stu.cellphone);
	printf("Marks:\n");
	for(i=0;i<SWN;i++)
	{
		printf("%-15s:%4d\n",schoolworks[i],stu.marks[i]);
	}
	printf("Total:%4d\n",stu.total);
	printf("**********************\n");
}

int add_stu(struct record s)
{
	int j;
	FILE *fp;
	fp = fopen(stuf,"at+");
	printf("\nInput student's name:");
	scanf("%s",&s.name);
	printf("\nInput student's code:");
	scanf("%s",&s.code);
	printf("\nInput student's sex:");
	scanf("%s",&s.sex);
	printf("\nInput student's birth:");
	scanf("%s",&s.birth);
	printf("\nInput student's hometown:");
	scanf("%s",&s.hometown);
	printf("\nInput student's cellphone:");
	scanf("%s",&s.cellphone);
	for(j=0;j<SWN;j++)
	{
		printf("\nInput the %s mark:",schoolworks[j]);
		scanf("%d",&s.marks[j]);
	}
	write_record(fp,&s);
	fclose(fp);
	return 1;
}

//按学号删除一个学生
int deleteone(char *fname)
{
	char *key;
	FILE *fp;
	FILE *t;
	char temp[FNAMELEN];//临时文件
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("\n Can't open file %s\n",fname);
		return 0; 	
	}
	printf("\nPlease input student's code you want to delete:");
	scanf("%s",key);
	t = fopen(temp,"w");
	while(read_record(fp,&s)!=0)
	{
		if(strcmp(s.code,key)!=0)
		{
			write_record(t,&s);
		}
	}
	fclose(fp);
	fclose(t);
	fp = fopen(fname,"w");
	t = fopen(temp,"r");
	while(read_record(t,&s)!=0)
	{
		write_record(fp,&s);
	}
	fclose(fp);
	fclose(t);
	return 1;
}

//按名字查找一个学生
void search_by_name(char buf[BUFLEN])
{
	FILE *fp;
	int c;
	struct record rc;
	printf("\nPlease input student's name you want to search:");
	scanf("%s",buf);
	if((fp=fopen(stuf,"r"))==NULL)
	{
		printf("\nPease creat file first!\n");
		return;
	}
	c = 0;
	while(read_record(fp,&rc)!=0)
	{
		if(strcmp(rc.name,buf)==0)
		{
			displaystu(rc);
			c++;
		}
	}
	fclose(fp);
	if(c==0)
	{
		printf("\nThe student %s is not in the record!\n",buf);
	}
}

void search_by_code(char buf[BUFLEN])
{
	struct record rc;
	printf("\nPlease input student's code you want to search:");
	scanf("%s",buf);
	if((fp=fopen(stuf,"r"))==NULL)
	{
		printf("\nPease creat file first!\n");
		return;
	}
	c = 0;
	while(read_record(fp,&rc)!=0)
	{
		if(strcmp(rc.code,buf)==0)
		{
			displaystu(rc);
			c++;
		}
	}
	fclose(fp);
	if(c==0)
	{
		printf("\nThe student whose code is %s not in the record!\n",buf);
	}
}

//按总分排序,返回一个排好序的链表 
struct record* sort_by_total_marks()
{
	FILE *fp;
	struct record s;
	struct record *p,*u,*v,*h;
	int i;
	if((fp=fopen(stuf,"r"))==NULL)
	{
		printf("\nCan't open file %s\n",stuf);
		return;	
	}
	h = NULL;
	p = (struct record*)malloc(sizeof(struct record));
	while(read_record(fp,p)!=0)
	{
		v = h;
		while(v&&p->total <= v->total)
		{
			u = v;
			v = v->next;
		}
		if(v == h)
		{
			h = p;
		}
		else
		{
			u->next = p;	
		}
		p->next = v;
		p = (struct record*)mallic(sizeof(struct record));
	}
	free(p);
	fclose(fp);
	return h;	
}
 
void list_stu(char *fname)
{
	FILE *fp;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("\nCan't open file %s.\n",fname);
		return;
	}
	while(read_record(fp,&s)!=0)
	{
		printf("\n\n"); 
		displaystu(s);
	}
	fclose(fp);
	printf("\nPress ENTER to continue...\n");
}

void show_menu()
{
	 char *f[]= {    
	 /*定义菜单字符串数组*/    
	 "**********Main*Menu***********",
	      " 0. add a new student",
	      " 1. delete a student",     
		  " 2. List all",       
		  " 3. search by name",     
		  " 4. search by code",     
		  " 5. search by birth",    
		  " 6. search by phone",     
		  " 7. sort by totalmark",     
		  " 8. sort by structure",     
		  " 9. sort by Mathmatic",      
		  " 10. sort by English",    
		  " 11. sort by age",     
		  " 12. sort by code",     
		  " 13. mean of marks",     
		  " 14. Total marks",      
		  " 15. number", 
	      " 16. Quit" ,
		  "****************************"};
	      int i = 0;
	      for(i=0;i<18;i++)
	      {
	      	printf("%s\n",f[i]);
		  }
		  printf("Please select the action you want...\n");  
}


int main()
{
	int i=0,j=0,n=0;
	char c;
	char stuname[20][20];
	int by,stunum=0;
	char buf[BUFLEN];
	FILE *fp;
	struct record s;
	system("cls");
	printf("Please input the students marks record file's name:\n");
	scanf("%s",stuf);
	if((fp=fopen(stuf,"r"))==NULL)
	{
		printf("The file %s doesn't exist,do you want to create it?(Y/N)\n",stuf);
		c = getchar();
		while(1)
		{
			if(c!='Y'&&c!='N')
			{
				printf("Please input again:\n");
				c=getchar();
			}
			else
			{
				break;
			}
		}
		if(c=='Y')
		{
			fp=fopen(stuf,"w");	
			printf("Please input the record number you want to write to file:\n");
			scanf("%d",&n);
			for(i = 0;i < n;i++)
			{
				printf("\nInput student's name:");
				scanf("%s",&s.name);
				printf("\nInput student's code:");
				scanf("%s",&s.code);
				printf("\nInput student's sex:");
				scanf("%s",&s.sex);
				printf("\nInput student's birth:");
				scanf("%s",&s.birth);
				printf("\nInput student's hometown:");
				scanf("%s",&s.hometown);
				printf("\nInput student's cellphone:");
				scanf("%s",&s.cellphone);
				for(j=0;j<SWN;j++)
				{
					printf("\nInput the %s mark:",schoolworks[j]);
					scanf("%d",&s.marks[j]);
				}
				write_record(fp,&s);
			}
			fclose(fp);
		}	
	}
	fclose(fp);
	system("cls");
	while(1)
	{
		system("cls");
		show_menu();
		getchar();
		c=getchar();
		switch(c)
		{
			case '0':
				//增加学生 
				system("cls");
				if(add_stu(s))
				{
					printf("\n add success!\n");	
				}
				break;
			case '1':
				//删除学生
				system("cls");
				if(deleteone(stuf))
				{
					printf("\n delete success!\n");	
				} 
				break;
			case '2':
				//列出全部记录 
				system("cls");
				list_stu(stuf);
				break;
			case '3':
				//按姓名查找
				system("cls");
				search_by_name(buf);
				break;
			case '4':
				//按学号查找
				system("cls");
				search_by_code(buf);
				break;
			case '5':
				//按总分排序
				system("cls");
				sort_by_total_marks(); 
				break;
			default:
				printf("\nPlease input a correct number\n");
				break;
		}
		system("pause");
	}
	return 0;
}
















































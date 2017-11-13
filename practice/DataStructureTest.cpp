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
#define BIRTHELEN 9
#define PHONELEN 12

char schoolworks[SWN][NAMELEN+1]={"DataStructure","Mathmatic","English"};

struct record
{
	char name[NAMELEN+1];
	char code[CODELEN+1];
	char sex[SEXLEN+1];
	char birth[BIRTHELEN+1];
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

void writeRecord(FILE *fp,struct record *rpt)
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

void add_stu(struct record s)
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
	writeRecord(fp,&s);
	fclose(fp);
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
		display(&s);
		printf("\nPress ENTER to continue...\n");
		while(getchar()!='\n');
	}
	fclose(fp);
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
	      " 16. Quit" };
	      int i = 0;
	      for(i=0;i<17;i++)
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
				writeRecord(fp,&s);
			}
			fclose(fp);
		}	
	}
	fclose(fp);
	system("cls");
	while(1)
	{
		show_menu();
		getchar();
		c=getchar();
		switch(c)
		{
			case '0':
				//增加学生 
				system("cls");
				add_stu(s);
				break;
			case '1':
				//删除学生 
				break;
			case '2':
				//列出全部记录 
				break;
			case '3':
				//按姓名查找 
				break;
			case '4':
				//按学号查找 
				break;
			case '5':
				//按生日查找 
				break 
		}
	}
	return 0;
}
















































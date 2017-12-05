#include<iostream>
#include<malloc.h>
#include<string>
using namespace std;

#define M 50
typedef struct 
{
	char name[10];
	char num[10];
	double grade;
}student;

//ֱ�Ӳ������� 
void insert_sort(student stus[],int n)
{
	int i,j;
	for(i=2;i <= n;i++)
	{
		j = i-1;
		stus[0].grade = stus[i].grade;
		while(stus[0].grade < stus[i].grade)
		{
			stus[j+1] = stus[j];
			j = j-1;
		}
		stus[j+1] = stus[0];
	}
}

//ֱ��ѡ������
void select_sort(student stus[],int n)
{
	int i,j,k; 
	for(i = 1;i <= n-1;i++)
	{
		k = i;
		for(j = i+1;j <= n;j++)
		{
			if(stus[i].grade > stus[j].grade)
			{
				k = j;
			}
			if(k != i)
			{
				stus[0] = stus[k];
				stus[k] = stus[i];
				stus[i] = stus[0];
			} 
		}
	}
} 

//��������
void quick_sort(student stus[],int left,int right)
{
	int i,j;
	if(left < right)
	{
		i = left;
		j = right;
		stus[0] = stus[i];//׼���Ա�������ߵ�Ԫ��Ϊ��׼���л��֣��ȱ�����ֵ
		do
		{
			while(stus[j].grade > stus[0].grade && i < j)
			{
				j--;
			}
			if(i < j)
			{
				stus[i] = stus[j];
				i++;
			}
			while(stus[i].grade < stus[0].grade &&i <j)
			{
				i++;
			}
			if(i < j)
			{
				stus[j]= stus[i];
				j--;
			}
		}while(i!=j);
		stus[i] = stus[0];
		quick_sort(stus,left,i-1);
		quick_sort(stus,i+1,right);
	}	
} 

int main()
{
	int i,n;
	student *stus,*s;
	cout<<"\n������ѧ������:"<<endl;
	cin>>n;
	stus = (student*)malloc((n+1)*sizeof(student));
	
	for(i = 1;i <= n;i++)
	{
		cout<<"\n�������"<<i<<"��ѧ��������:";
		cin>>stus[i].name;
		cout<<"\n�������"<<i<<"��ѧ����ѧ��:";
		cin>>stus[i].num;
		cout<<"\n�������"<<i<<"��ѧ���ĳɼ�:";
		cin>>stus[i].grade;
	}
	
	cout<<"\n�����:"<<endl; 
//	insert_sort(stus,n);
//	select_sort(stus,n);
	quick_sort(stus,1,n);
	for(i = 1;i <= n;i++)
	{
		cout<<"\n*************"<<endl;
		cout<<"����:"<<stus[i].name<<endl;
		cout<<"ѧ��:"<<stus[i].num<<endl;
		cout<<"�ɼ�:"<<stus[i].grade<<endl;
		cout<<"*************"<<endl; 
	}
}

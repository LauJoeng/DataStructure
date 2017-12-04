#include<iostream>
#include<string>
using namespace std;

class  TDate
{
	public:
		TDate(int y,int m,int d)
		{
			year = y;
			month = m;
			day = d;
		}
		void show()
		{
			cout<<year<<"年"<<month<<"月"<<day<<"日"<<endl; 
		}
	private:
		int year,month,day;
};

class people
{
	public:
		people(string n,int y,int m,int d,double s,string a):date(y,m,d)
		{
			name = n;
			stature = s;
			address = a;
		}
		void show()
		{
			cout<<"\n***************************************************************\n"<<endl;
			cout<<"name:"<<name<<endl;
			cout<<"birthday:";
			date.show();
			cout<<"stature:"<<stature<<"cm"<<endl;
			cout<<"address:"<<address<<endl;
			cout<<"\n****************************************************************\n"<<endl;
		}
	private:
		string name;
		TDate date;
		double stature;
		string address; 
};

int main()
{
	people p("张无忌",1876,6,1,187.6,"明教总部光明顶");
	p.show();
	return 0;
}

















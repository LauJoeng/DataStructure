#include<iostream>
using namespace std;

class shape
{
	public:
		virtual void show()=0;
} ;

 class dot: public shape
{
	public:
		dot(int x,int y)
		{
			this->x= x;
			this->y= y;
		}
		void show()
		{
			cout<<"this is a dot! it's coord is("<<x<<","<<y<<")"<<endl;
		}
	private:
		int x,y;
};

class rectangle:virtual public shape
{
	public:
		rectangle(double x,double y)
		{
			this->x = x;
			this->y = y;
		}
		void show()
		{
			cout<<"this is a rectangle! it's length is "<<x<<",it's width is "<<y<<endl;
		}
	private:
		double x,y;
};

class cycle:virtual public shape
{
	public:
		cycle(double r)
		{
			this->r = r;
		}
		void show()
		{
			cout<<"this is a cycle! it's radius is "<<r<<endl;
		}
	private:
		double r;
};

int main()
{
	shape *p;
	dot d(10,20);
	rectangle r(14.5,10.6);
	cycle c(4.4);
	p = &d;
	p->show();
	p=&r;
	p->show();
	p = &c;
	p->show();	
	return 0;
}


























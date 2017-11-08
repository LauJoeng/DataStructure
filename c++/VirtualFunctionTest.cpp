#include<iostream>
#include<math.h>
using namespace std;

class Shape
{
	public:
		Shape(double x)
		{
			r = x;	
		}
		virtual void area()=0;
		virtual void perimeter()=0;
	protected:
		double r;	
}; 

class CircumscribedTriangle:public Shape
{
	public:
		CircumscribedTriangle(double x):Shape(x){}
		void area()
		{
			cout<<"这个圆的外切正三角形的面积是:"<<((double)3/(double)2)*r*r<<endl;
		}
		void perimeter()
		{
			cout<<"这个圆的外切正三角形周长是:"<<3 * sqrt(3) * r<<endl;
		}		
};

class InscribedTriangle:public Shape
{
	public:
	 	InscribedTriangle(double x):Shape(x){}
		void area()
		{
			cout<<"这个圆的内切正三角形的面积是:"<<3*sqrt(3)/4*r*r<<endl;	
		} 
		void perimeter()
		{
			cout<<"这个圆的内切正三角形的周长是:"<<3 * sqrt(3) * r<<endl;
		}
};

//class CircumscribedTrapezoid:public Shape
//{
//	public:
//		CircumscribedTrapezoid(double x):Shape(x){}
//		void area()
//		{
//			cout<<"这个圆的外切等腰梯形面积为:"<<
//		}
//}

int main()
{
	Shape *ptr;
	CircumscribedTriangle ct(5);
	InscribedTriangle it(5);
	ptr = &ct;
	ptr->area();
	ptr->perimeter();
	ptr = &it;
	ptr->area();
	ptr->perimeter();
	return 0;
}

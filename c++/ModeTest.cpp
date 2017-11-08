#include<iostream>
using namespace std;

template<typename T>
class Sum
{
	public:
		Sum(T x,T y,T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		T getSum()
		{
			return x+y+z; 
		} 
	private:
		T x,y,z;	
}; 

int main()
{
	Sum<int> s1(1,2,3);
	Sum<float> s2(3.9,4.6,5.1);
	cout<<"int��1,2,3�������ֵĺ�Ϊ:"<<s1.getSum()<<endl;
	cout<<"float��3.9,4.6,5.1��������֮��Ϊ:"<<s2.getSum()<<endl;
	return 0;
}

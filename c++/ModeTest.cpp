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
	cout<<"int型1,2,3三个数字的和为:"<<s1.getSum()<<endl;
	cout<<"float型3.9,4.6,5.1三个数字之和为:"<<s2.getSum()<<endl;
	return 0;
}

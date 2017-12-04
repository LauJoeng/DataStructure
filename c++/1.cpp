#include<iostream>
using namespace std;

class vehicle
{
	public:
		virtual void run()
		{
			cout<<"vehicle::run() is called"<<endl;	
		}
		virtual void stop()
		{
			cout<<"veihcle::run() is called"<<endl;
		}
}; 

class bicycle:public vehicle 
{
	public:
		virtual void run()
		{
			cout<<"bicycle::run() is called"<<endl;	
		}
		virtual void stop()
		{
			cout<<"bivycle::run() is called"<<endl;
		}
};

class motorcar:public vehicle 
{
	public:
		virtual void run()
		{
			cout<<"motorcar::run() is called"<<endl;	
		}
		virtual void stop()
		{
			cout<<"motorcar::run() is called"<<endl;
		}
};

class motorcycle:public motorcar,public bicycle 
{
	public:
		virtual void run()
		{
			cout<<"motorcycle::run() is called"<<endl;	
		}
		virtual void stop()
		{
			cout<<"motorcycle::stop() is called"<<endl;
		}
};

int main()
{
	vehicle *p;
	bicycle b;
	motorcar m;
	motorcycle mc;
	p = &b;
	p->run();
	p->stop();
	
	p = &m;
	p->run();
	p->stop();
	
	mc.stop();
	mc.run();
	return 0;	
} 

























#ifndef _PROXY_PATTERN_H
#define _PROXY_PATTERN_H

#include <iostream>
#include <cstring>
using namespace std;

class SchoolGirl{
	private:
		char name[10];
	public:
		char* GetName(void){
			return name;
		}
		SchoolGirl(){}
		SchoolGirl(const char* name){
			strcpy(this->name,name);
		}
};

/* proxy interface */
class GiveGift{
	public:
		virtual void GiveDolls(void) = 0;
		virtual void GiveFlowers(void) = 0;
		virtual void GiveChocolate(void) = 0;
		virtual ~GiveGift(){
			cout<<"delete GiveGift."<<endl;
		}
};

class Pursuit : public GiveGift{
	private:
		SchoolGirl* mm;
	public:
		Pursuit(SchoolGirl* mm){
			this->mm = mm;
		}
		void GiveDolls(void){
			cout<<"give dolls to "<<mm->GetName()<<endl;
		}
		void GiveFlowers(void){
			cout<<"give flowers to "<<mm->GetName()<<endl;
		}
		void GiveChocolate(void){
			cout<<"give chocolate to "<<mm->GetName()<<endl;
		}
};

class Proxy : public GiveGift{
	private:
		Pursuit* gg;
	public:
		Proxy(SchoolGirl* mm){
			gg = new Pursuit(mm);
		}
		void GiveDolls(void){
			gg->GiveDolls();
		}
		void GiveFlowers(void){
			gg->GiveFlowers();
		}
		void GiveChocolate(void){
			gg->GiveChocolate();
		}
};

#endif



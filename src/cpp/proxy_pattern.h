#ifdef _PROXY_PATTERN_H
#define _PROXY_PATTERN_H

#include <iosstream>
using namespace std;

class SchoolGirl{
	private:
		char* name;
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
		SchoolGirl mm;
	public:
		Pursuit(SchoolGirl mm){
			this->mm = mm;
		}
		void GiveDolls(void){
			cout<<"give dolls to "<<mm.name<<endl;
		}
		void GiveFlowers(void){
			cout<<"give flowers to "<<mm.name<<endl;
		}
		void GiveChocolate(void){
			cout<<"give chocolate to "<<mm.name<<endl;
		}
};

class Proxy : public GiveGift{
	private:
		Pursuit gg;
	public:
		Proxy(SchoolGirl mm){
			gg = new Pursuit(mm);
		}
		void GiveDolls(void){
			gg.GiveDolls();
		}
		void GiveFlowers(void){
			gg.GiveFlowers();
		}
		void GiveChocolate(void){
			gg.GiveChocolate();
		}
};

#endif



#ifndef _STRATEGY_H
#define _STRATEGY_H

#include <iostream>
using namespace std;

class CashSuper{
	public:
		virtual double AcceptCash(double money) = 0;
		virtual ~CashSuper(){cout<<"delete CashSuper."<<endl;}
};

class CashNormal: public CashSuper{
	public:
		double AcceptCash(double money){
			return money;
		}
		~CashNormal(){cout<<"delete CashNormal."<<endl;}
};

class CashDiscount: public CashSuper{
	private:
		double discount;
	public:
		CashDiscount(double discount){
			this->discount = discount;
		}
		double AcceptCash(double money){
			return discount * money;
		}
};

class CashRebate: public CashSuper{
	private:
		double rebate_condition;
		double rebate_money;
	public:
		CashRebate(double rebate_condition, double rebate_money){
			this->rebate_condition = rebate_condition;
			this->rebate_money = rebate_money;
		}
		double AcceptCash(double money){
			double result;
			result = money;
			if(money >= rebate_condition){
				result = money - rebate_money;
			}
			return result;
		}
};

class CashContext{
	private:
		CashSuper* cashsuper;
	public:
		CashContext(){}
		CashContext(char opt){
			switch(opt){
			case 0:
				cashsuper = new CashNormal();
				break;
			case 1:
				cashsuper = new CashRebate(300,100);
				break;
			case 2:
				cashsuper = new CashDiscount(0.8);
				break;
			default:
				break;
			}
		}
		double GetResult(double money){
			return cashsuper->AcceptCash(money);
		}
		~CashContext(){
			cout<<"delete CashContext"<<endl;
			delete(cashsuper);
			//cout<<"delete CashContext"<<endl;
		}
};



#endif



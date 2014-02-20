#ifndef _STRATEGY_H
#define _STRATEGY_H

#include <iostream>
using namespace std;

class CashSuper{
	public:
		virtual double AcceptCash(double money) = 0;
};

class CashNormal: public CashSuper{
	public:
		double AcceptCash(double money){
			return money;
		}
};

class CashDiscount: public CashSuper{
	private:
		double discount = 1.0;
	public:
		CashDiscount(double discount){
			this.discount = discount;
		}
		double AcceptCash(double money){
			return discount * money;
		}
};

class CashRebate: public CashSuper{
	private:
		double rebate_condition = 0.0;
		double rebate_money = 0.0;
	public:
		CashRebate(double rebate_condition, double rebate_money){
			this.rebate_condition = rebate_condition;
			this.rebate_money = rebate_money;
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
		CashContext(CashSuper* cashsuper){
			this.cashsuper = cashsuper;
		}
		double GetResult(double money){
			return cashsuper->AcceptCash(money);
		}
};



#endif



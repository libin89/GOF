#ifndef _SIMPLE_FACTORY_H
#define _SIMPLE_FACTORY_H

#include <iostream>
#include <string>
using namespace std;

class Data{
	private:
		double ValueA, ValueB;
	public:
		void SetValueA(double value_a){ValueA = value_a;}
		double GetValueA(void){return ValueA;}
		void SetValueB(double value_b){ValueB = value_b;}
		double GetValueB(void){return ValueB;}
		virtual double GetResult(void){
			double result = 0;
			return result;
		}
};

class DataAdd: public Data{
	public:
		double GetResult(void){
			double result = 0;
			result = GetValueA() + GetValueB();
			return result;
		}	
};

class DataDiv: public Data{
	public:
		double GetResult(void){
			double result = 0;
			if(GetValueB() != 0){
				result = GetValueA() / GetValueB();
			}
			return result;
		}
};

class OperateFactory{
	public:
		static Data* OperateFun(char oper){
			Data* pDataObj = NULL;
			switch(oper)
			{
			case '+':
				 pDataObj = new DataAdd;
				break;
			case '/':
				pDataObj = new DataDiv;
				break;
			default:
				break;
			}
			return pDataObj;
		}
};

#endif




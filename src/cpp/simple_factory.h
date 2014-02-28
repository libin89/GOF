#ifndef _SIMPLE_FACTORY_H
#define _SIMPLE_FACTORY_H

#include <iostream>
#include <string>
using namespace std;

class Data{
	public:
		double ValueA;
		double ValueB;
		virtual double GetResult(void){
			double result = 0;
			return result;
		}
		virtual ~Data(){cout<<"delete Data."<<endl;}
};

class DataAdd: public Data{
	public:
		double GetResult(void){
			double result = 0;
			result = ValueA + ValueB;
			return result;
		}	
		~DataAdd(){cout<<"delete DataAdd."<<endl;}
};

class DataDiv: public Data{
	public:
		double GetResult(void){
			double result = 0;
			if(ValueB != 0){
				result = ValueA / ValueB;
			}
			return result;
		}
		~DataDiv(){cout<<"delete DataDiv."<<endl;}
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
		 ~OperateFactory(){
		 	cout<<"delete OperateFactory."<<endl;
		 }

};

#endif




#include "simple_factory.h"

int main(void){
	Data* data;
	double result;
	
	data = OperateFactory::OperateFun('+');
	data->ValueA = 1;
	data->ValueB = 2;
	result = data->GetResult();
	cout<<"Result = "<<result<<endl;
	return 0;	
}



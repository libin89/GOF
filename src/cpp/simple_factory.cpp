#include "simple_factory.h"

int main(void){
	Data* data;
	double result;
	
	data = OperateFactory::OperateFun('+');
	data->SetValueA(1);
	data->SetValueB(2);
	result = data->GetResult();
	cout<<"Result = "<<result<<endl;
	return 0;	
}

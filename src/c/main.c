#include "simple_factory.h"
#include <stdio.h>

int main(void)
{
	DataClass* pDerivedObj;
	double value_a;
	double value_b;
	char oper[5];

	while(1)
	{
		printf("Input ValueA : ");
		scanf("%lf",&value_a);
		printf("Input ValueB : ");
		scanf("%lf",&value_b);
		printf("Input Operate : ");
		scanf("%s",oper);
		pDerivedObj = new_operate_factory_class(value_a,value_b,oper);
		pDerivedObj->GetResult(value_a,value_b);
		delete_operate_factory_class(pDerivedObj);
		printf("\n");
	}
	

	return 0;
}
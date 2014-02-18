#include "simple_factory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

DataClass* new_data_class(double value_a, double value_b)
{
	DataClass* pBaseObj;

	pBaseObj = (DataClass*)malloc(sizeof(DataClass));
	if(pBaseObj == NULL)
	{
		return NULL;
	}
	pBaseObj->pDerivedObj = pBaseObj;
	pBaseObj->ValueA = value_a;
	pBaseObj->ValueB = value_b;
	pBaseObj->GetResult = get_result_add;

	return pBaseObj;
}

void delete_data_class(DataClass* data_obj)
{
	free(data_obj);
}

double get_result_add(double value_a, double value_b)
{
	printf("%lf + %lf = %lf\n",value_a,value_b,(value_a + value_b));
	return (value_a + value_b);
}

double get_result_div(double value_a, double value_b)
{
	if(value_b != 0)
	{
		printf("%lf / %lf = %lf\n",value_a,value_b,(value_a / value_b));
		return (value_a / value_b);
	}
	printf("除数不能为0\n");
	return 0;
}
double get_result_x_y(double value_a, double value_b)
{
	double result;

	if(value_a != 0)
	{
		result = pow(value_a,value_b);
		printf("%lf^%lf = %lf\n",value_a,value_b,result);
		return result;
	}
	printf("底数不能为0\n");
	return 0;
}

DataClass* new_operate_factory_class(double value_a, double value_b, char* oper)
{
	DataClass* pBaseObj;
	OperateFactoryClass* pDerivedObj;

	pBaseObj = new_data_class(value_a,value_b);
	pDerivedObj = malloc(sizeof(OperateFactoryClass));
	if(pDerivedObj == NULL)
	{
		delete_data_class(pBaseObj);
		return NULL;
	}
	pDerivedObj->Operate = (char*)malloc(sizeof(char)*strlen(oper)+1);
	strcpy(pDerivedObj->Operate,oper);
	pDerivedObj->pBaseObj = pBaseObj;
	pBaseObj->pDerivedObj = pDerivedObj;
	
	if(!strcmp(oper,"+"))
	{
		pBaseObj->GetResult = get_result_add;
	}
	if(!strcmp(oper,"/"))
	{
		pBaseObj->GetResult = get_result_div;
	}
	if(!strcmp(oper,"x^y"))
	{
		pBaseObj->GetResult = get_result_x_y;
	}

	return pBaseObj;
}

void delete_operate_factory_class(DataClass* data_obj)
{
	OperateFactoryClass* pDerivedObj;

	pDerivedObj = data_obj->pDerivedObj;
	free(pDerivedObj);
	free(data_obj);
}
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
	pBaseObj->ValueA = value_a;
	pBaseObj->ValueB = value_b;
	pBaseObj->GetResult = get_result_add;

	return pBaseObj;
}

void delete_data_class(DataClass* pData)
{
	free(pData);
}

double get_result_add(DataClass* pData)
{
	printf("%lf + %lf = %lf\n",pData->ValueA,pData->ValueB, \
                (pData->ValueA + pData->ValueB));
	return (pData->ValueA + pData->ValueB);
}

double get_result_div(DataClass* pData)
{
	if(pData->ValueB != 0)
	{
		printf("%lf / %lf = %lf\n",pData->ValueA,pData->ValueB, \
			(pData->ValueA + pData->ValueB));
		return (pData->ValueA + pData->ValueB);
	}
	printf("The divisor must not be 0.\n");
	return 0;
}
double get_result_x_y(DataClass* pData)
{
	double result;

	if(pData->ValueA != 0)
	{
		result = pow(pData->ValueA,pData->ValueB);
		printf("%lf^%lf = %lf\n",pData->ValueA,pData->ValueB,result);
		return result;
	}
	printf("The base number must not be 0.\n");
	return 0;
}

OperateFactory* new_operate_factory_class(DataClass* pBaseObj, char* oper)
{
	OperateFactoryClass* pFactory;

	pFactory = malloc(sizeof(OperateFactoryClass));
	if(pFactory == NULL)
	{
		return NULL;
	}
	pFactory->pBaseObj = pBaseObj;
	pFactory->Operate = (char*)malloc(sizeof(char)*strlen(oper)+1);
	strcpy(pFactory->Operate,oper);
	
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

	return pFactory;
}

void delete_operate_factory_class(DataClass* data_obj)
{
	OperateFactoryClass* pDerivedObj;

	pDerivedObj = data_obj->pDerivedObj;
	free(pDerivedObj);
	free(data_obj);
}

#ifndef _SIMPLE_FACTORY_H
#define _SIMPLE_FACTORY_H

typedef struct _DataClass {
	double ValueA;
	double ValueB;
	double (*GetResult) (struct _DataClass*);
}DataClass;

DataClass* new_data_class(double value_a, double value_b);
void delete_data_class(DataClass* pData);
double get_result_add(DataClass* pData);
double get_result_div(DataClass* pData);
double get_result_x_y(DataClass* pData);

typedef struct _OperateFactoryClass {
	DataClass* pBaseObj;
	char* Operate;
}OperateFactoryClass;

OperateFactory* new_operate_factory_class(DataClass* pBaseObj, char* oper);
void delete_operate_factory_class(OperateFactory* pFactory);

#endif



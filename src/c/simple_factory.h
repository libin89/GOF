#ifndef _SIMPLE_FACTORY_H
#define _SIMPLE_FACTORY_H

typedef struct _DataClass {
	void* pDerivedObj;
	double ValueA;
	double ValueB;
	double (*GetResult) (double, double);
}DataClass;

DataClass* new_data_class(double value_a, double value_b);
void delete_data_class(DataClass* data_obj);
double get_result_add(double value_a, double value_b);
double get_result_div(double value_a, double value_b);
double get_result_x_y(double value_a, double value_b);

typedef struct _OperateFactoryClass {
	DataClass* pBaseObj;
	char* Operate;
}OperateFactoryClass;

DataClass* new_operate_factory_class(double value_a, double value_b, char* oper);
void delete_operate_factory_class(DataClass* data_obj);

#endif
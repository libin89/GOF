#include "strategy.h"

int main(void){
	CashContext* context;
	double unit_price, total_price;
	int account;

	unit_price = 2.0;
	account = 10;
	total_price = unit_price * account;
	cout<<" 0-\"Normal\" \
		1-\"full 300 back 100\" \
		2-\"discount 0.8\""<<endl;
	context = new CashContext(0);
	total_price = context->GetResult(total_price);
	cout<<"Result = "<<total_price<<endl;
	delete(context);
}


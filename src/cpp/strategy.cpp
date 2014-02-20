#include "strategy.h"

int main(void){
	Context* context;
	double unit_price, total_price;
	int account;

	unit_price = 2.0;
	account = 10;
	total_price = unit_price * account;
	context = new Context(new CashNormal());
	total_price = context->GetResult(total_price);
	count<<"Result = "<<total_price<<endl;
}


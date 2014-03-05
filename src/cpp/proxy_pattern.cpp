#include "proxy_pattern.h"

int main(void){
	SchoolGirl* girl = new SchoolGirl();
	girl->name = "jiaojiao";

	Proxy* proxy = new Proxy(girl);

	proxy->GiveDolls();
	proxy->GiveFlowers();
	proxy->GiveChocolate();

	return 0;
}



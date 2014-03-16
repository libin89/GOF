#include "proxy_pattern.h"
#include <stdio.h>

int main(void)
{
	struct _school_girl* mm;
	struct _proxy* proxy;

	mm = new_school_girl("xixi");
	//printf("mm's name is %s\n",mm->name);
	proxy = new_proxy(mm);
	proxy->GiveDolls(mm);
	proxy->GiveFlowers(mm);
	proxy->GiveChocolate(mm);
	delete_school_girl(mm);
	delete_proxy(proxy);

	return 0;
}



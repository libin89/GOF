#include "proxy_pattern.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _school_girl* new_school_girl(const char* name){
	struct _school_girl* girl;

	girl = (struct _school_girl*)malloc(sizeof(struct _school_girl));
	if(girl == NULL){
		return NULL;
	}
	girl->name = (char*)malloc(sizeof(char)*strlen(name));
	strcpy(girl->name,name);

	return girl;
}

void delete_school_girl(void* girl){
	free(girl);
}

struct _proxy* new_proxy(struct _school_girl* girl){
	struct _proxy* proxy;
	
	proxy = (struct _proxy*)malloc(sizeof(struct _proxy));
	if(proxy == NULL){
		return NULL;
	}
	//proxy->girl = (struct _school_girl*)malloc(sizeof(struct _school_girl));
	proxy->girl = girl;
	proxy->GiveDolls = give_dolls;
	proxy->GiveFlowers = give_flowers;
	proxy->GiveChocolate = give_chocolate;

	return proxy;
}

void delete_proxy(void* proxy){
	free(proxy);
}


void give_dolls(struct _school_girl* girl){
	printf("give dolls to %s\n",girl->name);
}

void give_flowers(struct _school_girl* girl){
	printf("give flowers to %s\n",girl->name);
}

void give_chocolate(struct _school_girl* girl){
	printf("give chocolate to %s\n",girl->name);
}




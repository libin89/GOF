#ifndef PROXY_PATTERN_H
#define PROXY_PATTERN_H

struct _school_girl{
	char* name;
	};
struct _school_girl* new_school_girl(const char* name);
void delete_school_girl(void* girl);

struct _proxy{
	struct _school_girl* girl;
	void (*GiveDolls)(void*);
	void (*GiveFlowers)(void*);
	void (*GiveChocolate)(void*);
	};

struct _proxy* new_proxy(struct _school_girl* girl);
void delete_proxy(void* proxy);

void give_dolls(struct _school_girl* girl);
void give_flowers(struct _school_girl* girl);
void give_chocolate(struct _school_girl* girl);



#endif




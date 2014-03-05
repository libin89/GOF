#ifdef _DECORATOR_PATTERN_H
#define _DECORATOR_PATTERN_H

#include<iostream>
#include<cstring>
using namespace std;

class Person{
	private:
		char* name;
	public:
		Person(){}
		Person(char* name){
			strcpy(this->name,name);
		}
		virtual void Show(void){
			cout<<" of "<<name<<endl;
		}
};

class Finery : public Person{
	protected:
		Person person;
	public:
		void Decorate(Person person){
			this->person = person;
		}
		void Show(void){
			if(person != NULL){
				person.Show();
			}
		}
};

class TShirts : public Finery{
	void Show(void){
		cout<<" TShirt ";
		person.Show();
	}
};

class BigTrouser : public Finery{
	void Show(void){
		cout<<" BigTrouseer ";
		person.Show();
	}
};


#endif



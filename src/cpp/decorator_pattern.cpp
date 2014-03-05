#include "decorator_pattern.h"

int main(void){
	Person* li = new Person("li");
	TShirts* ts = new TShirts();
	BigTrouser* bt = new BigTrouser();

	ts->Decorate(li);
	bt->Decorate(ts);
	bt->Show();

	delete(bt);
	delete(ts);
	delete(li);

	return 0;
}



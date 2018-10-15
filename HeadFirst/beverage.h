/*************************************************
************ Decorator pattern *******************
* the demonstrated example introduction:
* first, have two keyword, beverage and condiment
* kinds of beverage below:
* HouseBlend DarkRoast Espresso Decaf
* kinds of condiment below:
* Milk Mocha Soy Whip
**************************************************
* so we can add any condiment in a beverage.
* for example, Milk + Soy + DarkRoast
* or, double Mocha + Decaf
* and we can have a description and calcurate cost.
**************************************************/
#ifndef _BEVERAGE_H
#define _BEVERAGE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Beverage {
    struct Beverage *beverage;
    char *description;
    double cost;
    char *(*getDescription)(struct Beverage *beverage);
    double (*getCost)(struct Beverage *beverage);
}Beverage;

void deleteBeverage(Beverage *beverage);
//Beverage
Beverage *newBeverage(Beverage *beverage, const char *desc, double cost);
//Condiment
Beverage *newCondiment(Beverage *beverage, const char *desc, double cost);

#endif

#include <string.h>
#include "beverage.h"

char *getDescription(struct Beverage * beverage)
{
    //printf("%s ", beverage->description);
    if(beverage->beverage)
        return strcat(beverage->getDescription(beverage->beverage), beverage->description);
    return beverage->description;
}
double getCost(struct Beverage *beverage)
{
    //printf("%f ", beverage->cost);
    if(beverage->beverage)
        return beverage->getCost(beverage->beverage) + beverage->cost;
    else
        return beverage->cost;
}
void deleteBeverage(Beverage *beverage)
{
    if (beverage->beverage) {
        deleteBeverage(beverage->beverage);
        printf("delete %s\n", beverage->description);
        free(beverage);
    }
    else {
        printf("delete %s\n", beverage->description);
        free(beverage);
    }
}

Beverage *newBeverage(Beverage *beverage, const char *desc, double cost)
{
    Beverage *bvrg = NULL;
    char *description = NULL;

    bvrg = (Beverage *)malloc(sizeof(Beverage));
    if (!bvrg) {
        printf("malloc error!\n");
        return NULL;
    }
    description = (char *)malloc(sizeof(char));
    if (!description) {
        printf("malloc error!\n");
        free(bvrg);
        return NULL;
    }
    strcpy(description, desc);
    bvrg->beverage = beverage;
    bvrg->description = description;
    bvrg->getDescription = getDescription;
    bvrg->cost = cost;
    bvrg->getCost = getCost;

    return bvrg;
}
Beverage *newCondiment(Beverage *beverage, const char *desc, double cost)
{
    Beverage *bvrg = NULL;
    char *description = NULL;

    bvrg = (Beverage *)malloc(sizeof(Beverage));
    if (!bvrg) {
        printf("malloc error!\n");
        return NULL;
    }
    description = (char *)malloc(sizeof(char));
    if (!description) {
        printf("malloc error!\n");
        free(bvrg);
        return NULL;
    }
    strcpy(description, desc);
    bvrg->beverage = beverage;
    bvrg->description = description;
    bvrg->getDescription = getDescription;
    bvrg->cost = cost;
    bvrg->getCost = getCost;

    return bvrg;
}

#ifdef BEVERAGE

int main(void)
{
    printf("Enter ...\n");
    Beverage *bvrg = newBeverage(NULL, "DarkRoast ", 1.2);
    Beverage *bvrg2 = newCondiment(bvrg, "Milk ", 0.3);
    bvrg2 = newCondiment(bvrg2, "Soy ", 0.4);
    printf("Description: %s\n", bvrg2->getDescription(bvrg2));
    printf("Total Cost: %f\n", bvrg2->getCost(bvrg2));

    deleteBeverage(bvrg2);
    printf("Exit ...\n");
    return 0;
}

#endif
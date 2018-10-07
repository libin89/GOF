#include "duck.h"

void FlyWithWings(void)
{
    printf("fly with wings.\n");
}

void FlyNoWay(void)
{
    printf("fly no way.\n");
}

void Quack(void)
{
    printf("quack.\n");
}

void Squeak(void)
{
    printf("squeak.\n");
}

void MuteQuack(void)
{
    printf("mute quack.\n");
}

void swim(void)
{
    printf("swim.\n");
}
void display(int whatKindOfDuck)
{
    printf("display:");
    switch(whatKindOfDuck) {
        case 0: //mallard duck
           printf("mallard duck.\n");
        break;
        default:
        break;
    }
}

void performQuack(struct Duck *duck)
{
    duck->quackBehavior();
}
void performFly(struct Duck *duck)
{
    duck->flyBehavior();
}

void setFlyBehavior(struct Duck *duck, FlyBehavior fb)
{
    printf("%s\n", __func__);
    duck->flyBehavior = fb;
}

Duck *newDuck(int whatKindOfDuck)
{
    Duck *duck = NULL;

    duck = (Duck *)malloc(sizeof(struct Duck));
    if (!duck) {
        printf("malloc error.\n");
        return NULL;
    }

    //initialize duck structure
    duck->swim = swim;
    duck->display = display;
    duck->performFly = performFly;
    duck->performQuack = performQuack;
    duck->setFlyBehavior = setFlyBehavior;
    switch(whatKindOfDuck) {
        case 0: //mallard duck
            duck->flyBehavior = FlyWithWings;
            duck->quackBehavior = MuteQuack; //mute quack
        break;
        default:
            duck->flyBehavior = FlyNoWay;
        break;
    }

    return duck;
}

void delete(Duck *duck)
{
    if (duck)
        free(duck);
}

int main(void)
{
    int whatKindOfDuck = 0;
    Duck *pDuck = newDuck(whatKindOfDuck);

    printf("enter...\n");

    pDuck->performFly(pDuck);
    pDuck->performQuack(pDuck);
    pDuck->swim();
    pDuck->display(whatKindOfDuck);

    // test setter fly behavior function
    pDuck->setFlyBehavior(pDuck, FlyNoWay);
    pDuck->performFly(pDuck);

    return 0;
}
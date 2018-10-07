/*********************************
*********Strategy pattern*********
**********************************/
#ifndef _DUCK_H
#define _DUCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*FlyBehavior)(void);
typedef void (*QuackBehavior)(void);
void swim(void);
void display(int whatKindOfDuck);

typedef struct Duck {
    FlyBehavior flyBehavior;
    QuackBehavior quackBehavior;
    void (*swim)(void);
    void (*display)(int whatKindOfDuck);
    void (*performQuack)(struct Duck *duck);
    void (*performFly)(struct Duck *duck);
    void (*setFlyBehavior)(struct Duck *duck, FlyBehavior fb);
}Duck;

#endif
/***********************************************
****************Observer Pattern****************
***********************************************/
#ifndef _WEATHER_H
#define _WEATHER_H

#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <stddef.h>

#ifndef offsetof
#define offsetof(TYPE, MEMBER) (size_t)&(((TYPE *)0)->MEMBER)
#endif

//WeatherData as a Subject class
typedef struct WeatherData {
    float temperature;
    float humidity;
    float pressure;
    void *conditionDisplayList; //need to initialize index list.
    void (*registerConditionDisplay)(struct WeatherData *wd, void *currentConditionDisplay);
    void (*removeConditionDisplay)(struct WeatherData *wd, void *currentConditionDisplay);
    void (*notifyConditionDisplays)(struct WeatherData *wd);
    void (*measurementChanged)(struct WeatherData *wd);
    void (*setMeasurements)(struct WeatherData *wd, float temp, float humidity, float pressure);

    //add some functions for push or pull data
    bool changed;
    void (*setChanged)(struct WeatherData *wd);
    void (*clearChanged)(struct WeatherData *wd);
    bool (*hasChanged)(struct WeatherData *wd);
    float (*getTemperature)(struct WeatherData *wd);
    float (*getHumidity)(struct WeatherData *wd);
    float (*getPressure)(struct WeatherData *wd);
}WeatherData;
struct WeatherData *newWeatherData(void);
void deleteWeatherData(struct WeatherData *wd);

//CurrentConditionDisplay as a Observer class
typedef struct CurrentConditionDisplay {
    int key; //distingguish different condition display instance
    float temperature;
    float humidity;
    void *weatherData;
    void (*update)(struct CurrentConditionDisplay *ccd, float temp, float humidity, float pressure);
    void (*display)(struct CurrentConditionDisplay *ccd);

    //add new update function to pull data from subject willingly
    void (*updateV2)(struct CurrentConditionDisplay *ccd);
}CurrentConditionDisplay;
struct CurrentConditionDisplay *newCurrentConditionDisplay(struct WeatherData *wd);
void deleteCurrentConditionDisplay(struct CurrentConditionDisplay *ccd);

#endif
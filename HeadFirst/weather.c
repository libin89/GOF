#include "weather.h"

/************************************************************************************
* suppose to have a index list class,  and have some functions to operate it.
* for example, add(void *object), remove(int objectNum), int indexOf(void *object),
* void *get(int objectNum), int size(void), void *initialize(void), delete(void *)
*************************************************************************************/
void (*setChanged)(struct WeatherData *wd)
{
    wd->changed = true;
}
void (*clearChanged)(struct WeatherData *wd)
{
    wd->changed = false;
}
bool (*hasChanged)(struct WeatherData *wd)
{
    return wd->changed;
}
float (*getTemperature)(struct WeatherData *wd)
{
    return wd->temperature;
}
float (*getHumidity)(struct WeatherData *wd)
{
    return wd->humidity;
}
float (*getPressure)(struct WeatherData *wd)
{
    return wd->pressure;
}
void (*registerConditionDisplay)(struct WeatherData *wd, void *currentConditionDisplay)
{
    CurrentConditionDisplay *ccd = (ConditionDisplay *)currentConditionDisplay;
    wd->conditionDisplayList.add(ccd);
}
void (*removeConditionDisplay)(struct WeatherData *wd, void *currentConditionDisplay)
{
    int i = wd->conditionDisplayList.indexOf((ConditionDisplay *)currentConditionDisplay);
    if (i >= 0) {
        wd->conditionDisplayList.remove(i);
    }
}
void (*notifyConditionDisplays)(struct WeatherData *wd)
{
    int i = 0;
    CurrentConditionDisplay *ccd = NULL;

    if (wd->hasChanged(wd)) {
        for (i = 0; i < wd->conditionDisplayList.size(); i++) {
            ccd = (CurrentConditionDisplay *)wd->conditionDisplayList.get(i);
            #if 0 //choice one of update functions accroding to need
            cd->update(cd, wd->temperature, wd->humidity, wd->pressure);
            #else
            ccd->updateV2(ccd);
            #endif
        }
        wd->clearChanged(wd);
    }
    
}
void (*measurementChanged)(struct WeatherData *wd)
{
    wd->setChanged(wd);
    wd->notifyConditionDisplays(wd);
}
void (*setMeasurements)(struct WeatherData *wd, float temp, float humidity, float pressure)
{
    wd->temperature = temp;
    wd->humidity = humidity;
    wd->pressure = pressure;
    wd->measurementChanged(wd);
}
struct WeatherData *newWeatherData(void)
{
    WeatherData *wd = NULL;
    CurrentConditionDisplay *ccd = NULL;

    wd = (WeatherData *)malloc(sizeof(struct WeatherData));
    if (!wd) {
        printf("malloc error!\n");
        return NULL;
    }

    ccd = (CurrentConditionDisplay *)malloc(sizeof(CurrentConditionDisplay));
    if (!ccd) {
        printf("malloc error!\n");
        free(wd);
        return NULL;
    }
    wd->conditionDisplayList = InitializeList(ccd); //initialize a list
    wd->registerConditionDisplay = registerConditionDisplay;
    wd->removeConditionDisplay = removeConditionDisplay;
    wd->notifyConditionDisplays = notifyConditionDisplays;
    wd->measurementChanged = measurementChanged;
    wd->setMeasurements = setMeasurements;

    return wd;
}
void deleteWeatherData(struct WeatherData *wd)
{
    if (wd)
        free(wd);
}

void (*update)(struct CurrentConditionDisplay *ccd, float temp, float humidity, float pressure)
{
    ccd->temperature = temp;
    ccd->humidity = humidity;
    ccd->pressure = pressure;
    ccd->display(ccd);
}
void (*updateV2)(struct CurrentConditionDisplay *ccd)
{
    ccd->temperature = ((WeatherData *)ccd->weatherData)->getTemperature;
    ccd->humidity = ((WeatherData *)ccd->weatherData)->getHumidity;
    ccd->display(ccd);
}
void (*display)(struct CurrentConditionDisplay *ccd)
{
    printf("Current Conditions: %d degrees and %d humidity", ccd->temperature, ccd->humidity);
}
struct CurrentConditionDisplay *newCurrentConditionDisplay(struct WeatherData *wd)
{
    CurrentConditionDisplay *ccd = NULL;

    ccd = (CurrentConditionDisplay *)malloc(sizeof(struct CurrentConditionDisplay));
    if (!ccd) {
        printf("malloc error!\n");
        return NULL;
    }
    ccd->weatherData = (void *)wd;
    ccd->update = update;
    ccd->display = display;
    wd->registerConditionDisplay(wd, ccd);

    return ccd;
}
void deleteCurrentConditionDisplay(struct CurrentConditionDisplay *ccd)
{
    if (ccd && ccd->weatherData) {
        wd->removeConditionDisplay((WeatherData *)ccd->weatherData, ccd);
        free(ccd);
    }
}
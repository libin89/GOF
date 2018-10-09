#include "weather.h"
#include "util/doublyLinkedList.h"

/************************************************************************************

*************************************************************************************/
void setChanged(struct WeatherData *wd)
{
    wd->changed = true;
}
void clearChanged(struct WeatherData *wd)
{
    wd->changed = false;
}
bool hasChanged(struct WeatherData *wd)
{
    return wd->changed;
}
float getTemperature(struct WeatherData *wd)
{
    return wd->temperature;
}
float getHumidity(struct WeatherData *wd)
{
    return wd->humidity;
}
float getPressure(struct WeatherData *wd)
{
    return wd->pressure;
}
void registerConditionDisplay(struct WeatherData *wd, void *currentConditionDisplay)
{
    CurrentConditionDisplay *ccd = (CurrentConditionDisplay *)currentConditionDisplay;
    doublyLinkedList *list = (doublyLinkedList *)wd->conditionDisplayList;

    listNode *node = newListNode((void *)ccd);
    list->push(list, node);
}
void removeConditionDisplay(struct WeatherData *wd, void *currentConditionDisplay)
{
    CurrentConditionDisplay *ccd = (CurrentConditionDisplay *)currentConditionDisplay;
    doublyLinkedList *list = (doublyLinkedList *)wd->conditionDisplayList;
    listNode * node = list->find(list, offsetof(CurrentConditionDisplay, key),\
        (void *)&(ccd->key), sizeof(int), 0, NULL, 0);
    if (node)
        list->removeNode(list, node);
}
void notifyConditionDisplays(struct WeatherData *wd)
{
    int i = 0;
    CurrentConditionDisplay *ccd = NULL;
    doublyLinkedList *list = (doublyLinkedList *)wd->conditionDisplayList;

    if (wd->hasChanged(wd)) {
        for (i = 0; i < list->size; i++) {
            ccd = (CurrentConditionDisplay *)(list->get(list, i)->data);
            #if 0 //choice one of update functions accroding to need
            cd->update(cd, wd->temperature, wd->humidity, wd->pressure);
            #else
            ccd->updateV2(ccd);
            #endif
        }
        wd->clearChanged(wd);
    }
    
}
void measurementChanged(struct WeatherData *wd)
{
    wd->setChanged(wd);
    wd->notifyConditionDisplays(wd);
}
void setMeasurements(struct WeatherData *wd, float temp, float humidity, float pressure)
{
    wd->temperature = temp;
    wd->humidity = humidity;
    wd->pressure = pressure;
    wd->measurementChanged(wd);
}
struct WeatherData *newWeatherData(void)
{
    WeatherData *wd = NULL;

    wd = (WeatherData *)malloc(sizeof(struct WeatherData));
    if (!wd) {
        printf("malloc error!\n");
        return NULL;
    }
    wd->conditionDisplayList = newList(NULL); //initialize a list
    if (!wd->conditionDisplayList) {
        printf("generate new list error.\n");
        free(wd);
        return NULL;
    }
    wd->registerConditionDisplay = registerConditionDisplay;
    wd->removeConditionDisplay = removeConditionDisplay;
    wd->notifyConditionDisplays = notifyConditionDisplays;
    wd->measurementChanged = measurementChanged;
    wd->setMeasurements = setMeasurements;
    wd->setChanged = setChanged;
    wd->clearChanged = clearChanged;
    wd->hasChanged = hasChanged;
    wd->getTemperature = getTemperature;
    wd->getHumidity = getHumidity;
    wd->getPressure = getPressure;

    return wd;
}
void deleteWeatherData(struct WeatherData *wd)
{
    if (wd) {
        deleteList((doublyLinkedList *)wd->conditionDisplayList);
        free(wd);
    }
}

void update(struct CurrentConditionDisplay *ccd, float temp, float humidity, float pressure)
{
    ccd->temperature = temp;
    ccd->humidity = humidity;
    ccd->pressure = pressure;
    ccd->display(ccd);
}
void updateV2(struct CurrentConditionDisplay *ccd)
{
    WeatherData *wd = (WeatherData *)ccd->weatherData;

    ccd->temperature = wd->getTemperature(wd);
    ccd->humidity = wd->getHumidity(wd);
    ccd->display(ccd);
}
void displayForecast(struct CurrentConditionDisplay *ccd)
{
    printf("%s, Current Conditions: %f degrees and %f humidity\n", __func__, ccd->temperature, ccd->humidity);
}
void displayCurrentSituation(struct CurrentConditionDisplay *ccd)
{
    printf("%s, Current Conditions: %f degrees and %f humidity\n", __func__, ccd->temperature, ccd->humidity);
}
struct CurrentConditionDisplay *newCurrentConditionDisplay(struct WeatherData *wd, int currentConditionDisplayKey)
{
    CurrentConditionDisplay *ccd = NULL;

    ccd = (CurrentConditionDisplay *)malloc(sizeof(struct CurrentConditionDisplay));
    if (!ccd) {
        printf("malloc error!\n");
        return NULL;
    }
    ccd->weatherData = (void *)wd;
    ccd->key = currentConditionDisplayKey;
    ccd->update = update;
    ccd->updateV2 = updateV2;
    switch (currentConditionDisplayKey) {
        case 0:
            ccd->display = displayForecast;
            break;
        case 1:
            ccd->display = displayCurrentSituation;
            break;
        default:
            break;
    }

    return ccd;
}
void deleteCurrentConditionDisplay(struct CurrentConditionDisplay *ccd)
{
    WeatherData *wd = (WeatherData *)ccd->weatherData;
    if (ccd && wd) {
        wd->removeConditionDisplay(wd, ccd);
        free(ccd);
    }
}

#ifdef WEATHER
int main(void)
{
    printf("Enter main...\n");
    WeatherData *wd = newWeatherData();
    CurrentConditionDisplay *displayForecast = newCurrentConditionDisplay(wd, 0);
    CurrentConditionDisplay *displayCurrentSituation = newCurrentConditionDisplay(wd, 1);

    //add displays to weather data
    ((WeatherData *)(displayForecast->weatherData))->registerConditionDisplay(wd, displayForecast);
    ((WeatherData *)(displayCurrentSituation->weatherData))->registerConditionDisplay(wd, displayCurrentSituation);

    //weather data changed
    wd->setMeasurements(wd, 35, 80.5f, 48.0f);
    wd->setMeasurements(wd, 55, 60.5f, 80);

    //display forecast cancle to observer weather data
    ((WeatherData *)(displayForecast->weatherData))->removeConditionDisplay(wd, displayForecast);
    wd->setMeasurements(wd, 25, 67, 90);

    deleteCurrentConditionDisplay(displayCurrentSituation);
    deleteCurrentConditionDisplay(displayForecast);
    deleteWeatherData(wd);
    printf("Exit main.\n");
    return 0;
}
#endif
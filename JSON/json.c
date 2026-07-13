#include <stdlib.h>
#include <stdio.h>

#include "cjson_import/cJSON.h"
#include "json.h"

void parseCoordinates(float *longitude, float *latitude, char *coordinateJSON) {
    cJSON *json = cJSON_Parse(coordinateJSON);

    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();

        if (error_ptr != NULL) {
            fprintf(stderr, "Error in parsing coordinate JSON: %s", error_ptr);
        }
        cJSON_Delete(json);
        exit(1);
    }

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (results == NULL || !cJSON_IsArray(results) || cJSON_GetArraySize(results) == 0) {
        fprintf(stderr, "No data found for the given city.\n");
        cJSON_Delete(json);
        exit(1);
    }

    cJSON *firstResult = cJSON_GetArrayItem(results, 0);

    cJSON *longt = cJSON_GetObjectItemCaseSensitive(firstResult, "longitude");
    if (longt->type == cJSON_Number) {
        (*longitude) = (float)longt->valuedouble;
    } cJSON *latit = cJSON_GetObjectItemCaseSensitive(firstResult, "latitude");
    if (latit->type == cJSON_Number) {
        (*latitude) = (float)latit->valuedouble;
    }

    cJSON_Delete(json);
}

void parseWeatherData(float *temp, float *wspeed, char *weatherDataJSON) {
    cJSON *json = cJSON_Parse(weatherDataJSON);

    if (json == NULL) {
       const char *error_ptr = cJSON_GetErrorPtr();

        if (error_ptr != NULL) {
            fprintf(stderr, "Error in parsing weather data JSON: %s", error_ptr);
        }
        cJSON_Delete(json);
        exit(1); 
    }

    cJSON *currentData = cJSON_GetObjectItemCaseSensitive(json, "current");
    if (currentData == NULL) {
        fprintf(stderr, "Couldn't find the required data from the JSON for the current weather data.\n");
        cJSON_Delete(json);
        exit(1);
    }

    cJSON *currentTemp = cJSON_GetObjectItemCaseSensitive(currentData, "temperature_2m");
    if (currentTemp != NULL && cJSON_IsNumber(currentTemp)) {
        (*temp) = (float)currentTemp->valuedouble;
    } cJSON *currentWSpeed = cJSON_GetObjectItemCaseSensitive(currentData, "wind_speed_10m");
    if (currentWSpeed != NULL && cJSON_IsNumber(currentWSpeed)) {
        (*wspeed) = (float)currentWSpeed->valuedouble;
    }

    cJSON_Delete(json);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "json.h"
#include "printing.h"

int main(int argc, char *argv[]) {
    char cityBuff[128] = {0}; /* Holds the city name */

    if (argc < 2) {
        fprintf(stderr, "Please provide a city name.\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (strlen(cityBuff) > 0) { strncat(cityBuff, " ", sizeof(cityBuff) - strlen(cityBuff) - 1); }

        strncat(cityBuff, argv[i], sizeof(cityBuff) - strlen(cityBuff) - 1);
    }
    cityBuff[127] = '\0';

    char requestURLBuffer[256]; /* This will hold the URL of the request for the given city's coordinates */

    /* GETTING THE COORDINATES FOR THE CITY */
    craftCoordinateRequest(cityBuff, requestURLBuffer);
    char *coordinateJSON = makeRequest(requestURLBuffer);
    if (coordinateJSON == NULL) { exit(1); }

    float city_longitude = 0.0;
    float city_latitude = 0.0;

    parseCoordinates(&city_longitude, &city_latitude, coordinateJSON);

    /* GETTING THE WEATHER DATA AND PRINTING IT */
    char weatherURLBuffer[256]; /* This will hold the URL used to fetch the weather data */
    snprintf(weatherURLBuffer, sizeof(weatherURLBuffer),
    "https://api.open-meteo.com/v1/forecast?latitude=%f&longitude=%f&current=temperature_2m,wind_speed_10m",
    city_latitude, city_longitude);

    char *weatherDataJSON = makeRequest(weatherURLBuffer);
    if (weatherDataJSON == NULL) { exit(1); }

    float temperature = 0;
    float wind_speed = 0;

    parseWeatherData(&temperature, &wind_speed, weatherDataJSON);

    printWeatherData(cityBuff, temperature, wind_speed);

    free(coordinateJSON);
    free(weatherDataJSON);
    return EXIT_SUCCESS;
}
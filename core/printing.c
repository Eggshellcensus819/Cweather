#include <stdio.h>
#include "printing.h"

// Terminal UI colors
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BLUE    "\033[34m"

void printWeatherData(char *cityName, float temp, float wspeed) {
    printf("\n" COLOR_BOLD "--- Weather Data for '%s' ---" COLOR_RESET "\n\n", cityName);

    if (temp >= 30.0) {
        printf("Temperature: " COLOR_RED "%.2f°C" COLOR_RESET ", it's hot outside! 🥵\n", temp);
    } else if (temp >= 20.0) {
        printf("Temperature: " COLOR_YELLOW "%.2f°C" COLOR_RESET ", it's warm outside 🌡️\n", temp); 
    } else if (temp >= 10.0) {
        printf("Temperature: " COLOR_CYAN "%.2f°C" COLOR_RESET ", it's cool outside 😎\n", temp);
    } else if (temp > 0.0) {
        printf("Temperature: " COLOR_BLUE "%.2f°C" COLOR_RESET ", it's cold outside 🥶\n", temp);
    } else {
        printf("Temperature: " COLOR_BOLD COLOR_BLUE "%.2f°C" COLOR_RESET ", it's freezing outside! ❄️\n", temp);
    }

    /* This is based on the "Beuafort scale", you can find it at: https://en.wikipedia.org/wiki/Beaufort_scale */
    if (wspeed >= 118.0) {
        printf("Wind Speed:  %.2f km/h, there might be a hurricane outside! 🌪️\n", wspeed);
    } else if (wspeed >= 62.0) {
        printf("Wind Speed:  %.2f km/h, be careful, it's extremely windy outside! 💨\n", wspeed);
    } else if (wspeed >= 29.0) {
        printf("Wind Speed:  %.2f km/h, it's pretty windy outside, watch out for falling branches! 🌬️\n", wspeed);
    } else if (wspeed >= 12.0) {
        printf("Wind Speed:  %.2f km/h, it's breezy outside 🍃\n", wspeed);
    } else {
        printf("Wind Speed:  %.2f km/h, it's very calm outside 🧘\n", wspeed);
    }
    
    printf("\n------------------------------------\n");
}
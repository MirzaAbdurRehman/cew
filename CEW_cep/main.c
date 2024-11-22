#include "weather_system.h"
#include "alert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *city = "Karachi";

    printf("------Weather Alert System (Automated)------\n");
    printf("=============================================\n\n");

    printf("Fetching weather data for %s...\n", city);
    get_weather_data(city);

    printf("\nWeather data processing complete.\n");
    printf("===================================\n");

    return 0;
}


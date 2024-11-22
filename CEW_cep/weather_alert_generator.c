#include "weather_system.h"
#include "alert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_weather_data(const char *city) {
    char *api_key = "5cc3d0cfb411427fb070b0b9a27583ff";  // Weatherbit API key
    char command[256];

    snprintf(command, sizeof(command), "curl -s \"http://api.weatherbit.io/v2.0/current?city=%s&key=%s\"", city, api_key);
    FILE *fp = popen(command, "r");

    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char *result = malloc(1024 * sizeof(char));
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    fread(result, 1, 1024 - 1, fp);
    pclose(fp);

    float temperature = 0.0, humidity = 0.0, pressure = 0.0, precipitation = 0.0, uv_index = 0.0;

    char *temp_ptr = strstr(result, "\"temp\":");
    char *humidity_ptr = strstr(result, "\"rh\":");
    char *pressure_ptr = strstr(result, "\"pres\":");
    char *precipitation_ptr = strstr(result, "\"precip\":");
    char *uv_index_ptr = strstr(result, "\"uv\":");

    if (temp_ptr) {
        sscanf(temp_ptr, "\"temp\":%f", &temperature);
    }
    if (humidity_ptr) {
        sscanf(humidity_ptr, "\"rh\":%f", &humidity);
    }
    if (pressure_ptr) {
        sscanf(pressure_ptr, "\"pres\":%f", &pressure);
    }
    if (precipitation_ptr) {
        sscanf(precipitation_ptr, "\"precip\":%f", &precipitation);
    }
    if (uv_index_ptr) {
        sscanf(uv_index_ptr, "\"uv\":%f", &uv_index);
    }

    printf("Processed Weather Data:\n");
    printf("Temperature: %.2f°C, Humidity: %.2f%%, Pressure: %.2f hPa, Precipitation: %.2f mm, UV Index: %.2f\n\n",
           temperature, humidity, pressure, precipitation, uv_index);

    FILE *file = fopen("weather_data.txt", "a");
    if (file == NULL) {
        perror("Unable to open file for raw data");
        exit(1);
    }
    fprintf(file, "%s\n", result);
    fclose(file);

    file = fopen("processed_data.txt", "a");
    if (file == NULL) {
        perror("Unable to open file for processed data");
        exit(1);
    }
    fprintf(file, "Temperature: %.2f, Humidity: %.2f, Pressure: %.2f, Precipitation: %.2f, UV Index: %.2f\n",
            temperature, humidity, pressure, precipitation, uv_index);
    fclose(file);

    float temp_threshold = 20.0;
    float humidity_threshold = 90.0;
    float uv_threshold = 8.0;

    if (temperature > temp_threshold) {
        char alert_message[100];
        snprintf(alert_message, sizeof(alert_message), "Alert! Temperature exceeds threshold: %.2f°C", temperature);
        notify_alert(alert_message, 2);
    }

    if (humidity > humidity_threshold) {
        char alert_message[100];
        snprintf(alert_message, sizeof(alert_message), "Alert! Humidity exceeds threshold: %.2f%%", humidity);
        notify_alert(alert_message, 2);
    }

    if (uv_index > uv_threshold) {
        char alert_message[100];
        snprintf(alert_message, sizeof(alert_message), "Alert! UV Index exceeds threshold: %.2f", uv_index);
        notify_alert(alert_message, 2);
    }

    free(result);
}

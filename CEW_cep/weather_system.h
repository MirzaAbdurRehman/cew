#ifndef WEATHER_H
#define WEATHER_H

void get_weather_data(const char *city);
void notify_alert(const char *message, int severity);

#endif // WEATHER_H

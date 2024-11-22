#include "alert.h"
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

void notify_alert(const char *message, int severity) {
    printf("Sending alert: %s\n", message);

    openlog("weather_alert", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "%s", message);
    closelog();

    if (severity > 1) {
        char email_command[512];
        snprintf(email_command, sizeof(email_command), "echo \"%s\" | mail -s \"Weather Alert Notification\" shafiaarif26@gmail.com", message);

        int email_status = system(email_command);
        if (email_status != 0) {
            printf("Failed to send email alert. Please check your mail configuration.\n");
            openlog("weather_alert", LOG_PID | LOG_CONS, LOG_USER);
            syslog(LOG_ERR, "Email failed to send: %s", message);
            closelog();
        } else {
            printf("Email alert sent successfully.\n");
        }
    }
}

#include <stdio.h>
#include <time.h>
#include "logger.h"

void logOperation(const char *operation, const char *result) {
    FILE *logFile = fopen("operations.log", "a");
    if (logFile == NULL) {
        perror("Error opening log file");
        return;
    }
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timeStr[26];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(logFile, "[%s] %s: %s\n", timeStr, operation, result);
    fclose(logFile);
}


#ifndef LOG_H
#define LOG_H

typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_NOTICE = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_CRITICAL = 4
} log_level_t;

void LogMessage(unsigned char level, const char *message, unsigned int size);
void LogCString(unsigned char level, const char *message);

#endif

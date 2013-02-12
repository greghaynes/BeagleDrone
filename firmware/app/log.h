#ifndef LOG_H
#define LOG_H

#define LOG_LEVEL_DEBUG     0
#define LOG_LEVEL_NOTICE    1
#define LOG_LEVEL_WARNING   2
#define LOG_LEVEL_ERROR     3
#define LOG_LEVEL_CRITICAL  4

void LogMessage(unsigned char level, const char *message, unsigned int size);
void LogCString(unsigned char level, const char *message);

#endif

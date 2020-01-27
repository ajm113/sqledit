#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_LEVEL_DEBUG   0
#define LOG_LEVEL_MESSAGE 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR   3

#define LOG_LEVEL_DEBUG_TEXT    "DEBUG"
#define LOG_LEVEL_MESSAGE_TEXT  "MESSAGE"
#define LOG_LEVEL_WARNING_TEXT  "WARNING"
#define LOG_LEVEL_ERROR_TEXT    "ERROR"

#define LOG_TYPE_NONE               0
#define LOG_TYPE_CONSOLE            1
#define LOG_TYPE_FILE               2
#define LOG_TYPE_FILE_AND_CONSOLE   3

struct SQLEditLogger {
  short logLevel;
  short outputMode;

  FILE *fp;
};

struct SQLEditLogger* sqledit_logger_init(const char* filename, int truncate, short logLevel, short outputMode);
void sqledit_logger_close(struct SQLEditLogger* log);

void sqledit_logger_debug(struct SQLEditLogger* log, const char* message);
void sqledit_logger_message(struct SQLEditLogger* log, const char* message);
void sqledit_logger_warning(struct SQLEditLogger* log, const char* message);
void sqledit_logger_error(struct SQLEditLogger* log, const char* message);

char* sqledit_logger_format_message(const char* message, short logLevel);
void sqledit_logger_display_message(struct SQLEditLogger* log, const char* message, short logLevel);


#endif

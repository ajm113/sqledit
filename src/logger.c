#include "logger.h"

struct SQLEditLogger* sqledit_logger_init(const char* filename, int truncate, short logLevel, short outputMode) {
  struct SQLEditLogger* log = malloc(sizeof(struct SQLEditLogger));

  log->logLevel = logLevel;
  log->outputMode = outputMode;


  switch (outputMode)
  {
  case LOG_TYPE_FILE:
  case LOG_TYPE_FILE_AND_CONSOLE: {
    if (truncate) {
      log->fp = fopen(filename, "w");
    } else {
      log->fp = fopen(filename, "w+");
    }
    break;
  }
  }

  return log;
}

void sqledit_logger_close(struct SQLEditLogger* log) {
  if(log == NULL) {
    return;
  }

  if (log->fp != NULL) {
    fclose(log->fp);
  }

  free(log);
  log = NULL;
}

void sqledit_logger_debug(struct SQLEditLogger* log, const char* message) {
  sqledit_logger_display_message(log, message, LOG_LEVEL_DEBUG);
}
void sqledit_logger_message(struct SQLEditLogger* log, const char* message) {
  sqledit_logger_display_message(log, message, LOG_LEVEL_MESSAGE);
}
void sqledit_logger_warning(struct SQLEditLogger* log, const char* message) {
  sqledit_logger_display_message(log, message, LOG_LEVEL_WARNING);
}
void sqledit_logger_error(struct SQLEditLogger* log, const char* message) {
  sqledit_logger_display_message(log, message, LOG_LEVEL_ERROR);
}

char* sqledit_logger_format_message(const char* message, short logLevel) {
  char* messageTypeString;

  switch (logLevel)
  {
  case LOG_LEVEL_DEBUG:
    messageTypeString = LOG_LEVEL_DEBUG_TEXT;
    break;
  case LOG_LEVEL_MESSAGE:
    messageTypeString = LOG_LEVEL_MESSAGE_TEXT;
    break;
  case LOG_LEVEL_WARNING:
    messageTypeString = LOG_LEVEL_WARNING_TEXT;
    break;
  case LOG_LEVEL_ERROR:
    messageTypeString = LOG_LEVEL_ERROR_TEXT;
    break;
  }

  // New formated message length. Includes braces and string terminator.
  const size_t formatedMessageLength = sizeof(char) * strlen(message) + strlen(messageTypeString) + 4;
  char* buf = malloc(formatedMessageLength);
  snprintf(buf, formatedMessageLength, "[%s] %s", messageTypeString, message);

  return buf;
}

void sqledit_logger_display_message(struct SQLEditLogger* log, const char* message, short logLevel) {
  if (log->logLevel > logLevel) {
    return;
  }

  char* formatedMessage = sqledit_logger_format_message(message, logLevel);

  if (log->outputMode == LOG_TYPE_CONSOLE || log->outputMode == LOG_TYPE_FILE_AND_CONSOLE) {
    switch(logLevel) {
      case LOG_LEVEL_DEBUG:
      case LOG_LEVEL_MESSAGE:
        printf("%s\n", formatedMessage);
        break;
      default:
        fprintf(stderr, "%s\n", formatedMessage);
    }
  }

  if (log->outputMode == LOG_TYPE_FILE || log->outputMode == LOG_TYPE_FILE_AND_CONSOLE) {
    fprintf(log->fp, "%s\n", formatedMessage);
  }

  free(formatedMessage);
}

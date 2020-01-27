#ifndef SQLEDIT_H
#define SQLEDIT_H

#include <gtk/gtk.h>

#include "logger.h"

#define APP_NAME "SQLEdit"
#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 0

struct SQLEditApp {
  GtkWidget *window;
  struct SQLEditLogger* log;
};

void sqledit_create_main_window(struct SQLEditApp* app);


#endif

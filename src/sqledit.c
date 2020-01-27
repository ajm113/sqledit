#include "sqledit.h"

void sqledit_create_main_window(struct SQLEditApp* app) {
  app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(app->window), APP_NAME);
  gtk_window_set_default_size(GTK_WINDOW(app->window), 1024, 600);
  gtk_window_set_position(GTK_WINDOW(app->window), GTK_WIN_POS_CENTER);

  g_signal_connect(G_OBJECT(app->window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  return;
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  struct SQLEditApp* app = &(struct SQLEditApp) {};

  app->log = sqledit_logger_init("sqledit.log", 1, LOG_LEVEL_DEBUG, LOG_TYPE_FILE_AND_CONSOLE);

  sqledit_logger_message(app->log, "Starting " APP_NAME "...");
  sqledit_create_main_window(app);

  gtk_widget_show(app->window);
  gtk_main();

  sqledit_logger_close(app->log);
  app = NULL;
  return 0;
}

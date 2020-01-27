#include "sqledit.h"

void sqledit_create_main_window(struct SQLEditApp* app) {

  // Setup main window.
  app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(app->window), APP_NAME);
  gtk_window_set_default_size(GTK_WINDOW(app->window), 1024, 600);
  gtk_window_set_position(GTK_WINDOW(app->window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(app->window), 1);

  g_signal_connect(G_OBJECT(app->window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  // Setup Status Bar.
  app->statusBarBox = gtk_alignment_new(0, 1, 0, 0);
  gtk_container_add(GTK_CONTAINER(app->window), app->statusBarBox);
  gtk_widget_show(app->statusBarBox);

  app->statusBar = gtk_statusbar_new();
  gtk_container_add(GTK_CONTAINER(app->statusBarBox), app->statusBar);
  gtk_widget_show(app->statusBar);

  app->statusBarContextId = gtk_statusbar_get_context_id(GTK_STATUSBAR(app->statusBar), "Statusbar");
  gtk_statusbar_push(GTK_STATUSBAR(app->statusBar), app->statusBarContextId, "Nothing to show...");

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

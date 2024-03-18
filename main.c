#include <gtk/gtk.h>
#include <glib/gstdio.h>


static void print_hello(GtkWidget* widget, gpointer data){
  g_print("Hello World\n");
}

static void quit_cb(GtkWindow* window){
  gtk_window_close(window);
}

static void activate(GtkApplication* app, gpointer data){
  /* create GtkBuilder & load UI */ 
  GtkBuilder* builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "builder.ui", NULL);

  /* connect signal handlers to widgets */
  GObject* window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject* button = gtk_builder_get_object(builder, "button1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  button = gtk_builder_get_object(builder, "button2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  button = gtk_builder_get_object(builder, "quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb), window);

  gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
  
  // we don't need the builder anymore
  g_object_unref(builder);

}

int main(int argc, char** argv){
  #ifdef GTK_SRCDIR
    g_chdir(GTK_SRCDIR);
  #endif /* ifdef GTK_SRCDIR */

  GtkApplication* app = gtk_application_new("org.gtk.app", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

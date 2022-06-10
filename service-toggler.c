#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget* service_name_entry;

/* Button callbacks */
void button_callback(GtkWidget* clicked_widget, gpointer data){
    char* button_name = (char *) data;
    const gchar* service_name = gtk_entry_get_text(GTK_ENTRY (service_name_entry));
    // Run service command
    char command_buffer[256];
    snprintf(command_buffer, 255, "sudo service %s %s", service_name, button_name);
    system(command_buffer);
    fflush(stdout);
}

GtkWidget* create_button(char* text, void* callback){
  GtkWidget* button = gtk_button_new_with_label(text);
  g_signal_connect(G_OBJECT(button), "clicked",
    G_CALLBACK(callback), text);
  return button;

}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window, *primary_grid, *button_grid;
  GtkWidget *service_name_label; 
  GtkWidget *start_button, *stop_button, *restart_button;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_container_set_border_width (GTK_CONTAINER (window), 20);
  // Create primary grid
  primary_grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), primary_grid);
  // Create button grid
  button_grid = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(primary_grid), button_grid, 0, 1, 2, 1);
  // Service name entry
  service_name_label = gtk_label_new("Service name: ");
  service_name_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(service_name_entry), "Service name");
  gtk_grid_attach(GTK_GRID(primary_grid), service_name_label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(primary_grid), service_name_entry, 1, 0, 1, 1);
  // Start, stop, restart buttons
  start_button = create_button("start", button_callback);  
  stop_button = create_button("stop", button_callback);  
  restart_button = create_button("restart", button_callback);  
  gtk_grid_attach(GTK_GRID(button_grid), start_button, 0, 0, 1, 1); 
  gtk_grid_attach(GTK_GRID(button_grid), stop_button, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(button_grid), restart_button, 2, 0, 1, 1);
  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

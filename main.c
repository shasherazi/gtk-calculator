#include "calculator.h"
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;

  // calculator state
  struct calculator *calculator = malloc(sizeof(struct calculator));

  // display
  GdkDisplay *display = gdk_display_get_default();

  // load styles.css
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "styles.css");
  gtk_style_context_add_provider_for_display(
      display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Calculator");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
  gtk_window_present(GTK_WINDOW(window));

  // create a gtk vertical box. top will be a text and bottom will be the
  // buttons grid. make elements expandable
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  gtk_window_set_child(GTK_WINDOW(window), vbox);

  // calculator text
  GtkWidget *label = gtk_label_new("0");
  gtk_widget_add_css_class(GTK_WIDGET(label), "text");
  gtk_widget_set_size_request(GTK_WIDGET(label), 0, 100);
  gtk_label_set_xalign(GTK_LABEL(label), 0.9);
  gtk_widget_set_hexpand(GTK_WIDGET(label), TRUE);
  gtk_box_append(GTK_BOX(vbox), GTK_WIDGET(label));

  GtkWidget *grid = create_calculator_grid();
  gtk_box_append(GTK_BOX(vbox), grid);

  calculator->result = 0;
  calculator->operator= 0;
  calculator->operand = 0;
  calculator->label = GTK_LABEL(label);

  // calculator buttons
  GtkWidget **buttons = create_buttons();

  // connect all buttons to calculator_button_clicked
  for (int i = 0; i < 16; i++) {
    g_signal_connect(buttons[i], "clicked",
                     G_CALLBACK(calculator_button_clicked), calculator);
  }

  // setting 1 button to expand vertically makes
  // all buttons expand vertically somehow
  gtk_widget_set_vexpand(buttons[0], TRUE);

  attach_buttons_to_grid(grid, buttons);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.example.calculator",
                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

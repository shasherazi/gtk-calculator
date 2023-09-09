#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <gtk/gtk.h>

struct calculator {
  double result;
  double operand;
  char operator;
  GtkLabel *label;
};

GtkWidget *create_calculator_grid(void);
GtkWidget **create_buttons(void);
void attach_buttons_to_grid(GtkWidget *grid, GtkWidget **buttons);
void calculator_button_clicked(GtkWidget *widget, gpointer data);
double operate(struct calculator *calc);

#endif // CALCULATOR_H

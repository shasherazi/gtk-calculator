#include "calculator.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *create_calculator_grid() {
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  return grid;
}

GtkWidget **create_buttons() {
  // mallocing coz local variables are destroyed after function returns
  GtkWidget **buttons = malloc(sizeof(GtkWidget *) * 16);

  buttons[0] = gtk_button_new_with_label("7");
  buttons[1] = gtk_button_new_with_label("8");
  buttons[2] = gtk_button_new_with_label("9");
  buttons[3] = gtk_button_new_with_label("/");
  buttons[4] = gtk_button_new_with_label("4");
  buttons[5] = gtk_button_new_with_label("5");
  buttons[6] = gtk_button_new_with_label("6");
  buttons[7] = gtk_button_new_with_label("*");
  buttons[8] = gtk_button_new_with_label("1");
  buttons[9] = gtk_button_new_with_label("2");
  buttons[10] = gtk_button_new_with_label("3");
  buttons[11] = gtk_button_new_with_label("-");
  buttons[12] = gtk_button_new_with_label("0");
  buttons[13] = gtk_button_new_with_label(".");
  buttons[14] = gtk_button_new_with_label("=");
  buttons[15] = gtk_button_new_with_label("+");
  return buttons;
}

void attach_buttons_to_grid(GtkWidget *grid, GtkWidget **buttons) {
  gtk_grid_attach(GTK_GRID(grid), buttons[0], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[1], 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[2], 2, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[3], 3, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[4], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[5], 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[6], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[7], 3, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[8], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[9], 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[10], 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[11], 3, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[12], 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[13], 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[14], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttons[15], 3, 3, 1, 1);
}

double operate(struct calculator *calc) {
  switch (calc->operator) {
  case '+':
    return calc->result + calc->operand;
  case '-':
    return calc->result - calc->operand;
  case '*':
    return calc->result * calc->operand;
  case '/':
    return calc->result / calc->operand;
  default:
    return calc->operand;
  }
}

void calculator_button_clicked(GtkWidget *widget, gpointer data) {
  struct calculator *calculator = (struct calculator *)data;
  GtkButton *button = GTK_BUTTON(widget);
  const char *button_label = gtk_button_get_label(button);
  const char *label_text = gtk_label_get_label(calculator->label);

  if (isdigit(*button_label) || (strcmp(button_label, ".") == 0)) {
    // If the button clicked is a digit or ".", update the operand and display
    char new_text[256];
    snprintf(new_text, sizeof(new_text), "%s%s", label_text, button_label);
    gtk_label_set_label(calculator->label, new_text);
    calculator->operand = atof(new_text);
  } else if (strcmp(button_label, "=") == 0) {
    // If the button clicked is "=", perform the calculation and update the
    // display
    double result = operate(calculator);
    char result_text[256];
    snprintf(result_text, sizeof(result_text), "%g", result);
    gtk_label_set_label(calculator->label, result_text);
    calculator->operand = result;
  } else {
    // If an operator button is clicked, set the operator in the calculator
    calculator->operator= * button_label;
    calculator->result = calculator->operand;
    calculator->operand = 0;
    gtk_label_set_label(calculator->label, ""); // Clear the display
  }
}

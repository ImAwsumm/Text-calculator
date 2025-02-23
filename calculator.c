#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>

#define MAX_EXPR_LEN 256

// Function to process the input equation
double calculate(const char *equation) {
    char math_phrase[MAX_EXPR_LEN];
    strcpy(math_phrase, equation);
    
    // Time start
    clock_t start = clock();
    
    // Handle multiplication and division first
    double muldiv_lst[MAX_EXPR_LEN];
    char operators[MAX_EXPR_LEN];
    int num_count = 0, op_count = 0;
    
    // Split the string into numbers and operators
    char *token = strtok(math_phrase, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            muldiv_lst[num_count++] = atof(token);
        } else {
            operators[op_count++] = token[0];
        }
        token = strtok(NULL, " ");
    }

void on_calculate_button_clicked(GtkWidget *widget, gpointer data) {
    const char *expression = gtk_entry_get_text(GTK_ENTRY(data));
    double result = calculate(expression);
    char result_text[MAX_EXPR_LEN];
    snprintf(result_text, sizeof(result_text), "Result: %.2f", result);
    gtk_label_set_text(GTK_LABEL(gtk_widget_get_parent(widget)), result_text);
}

int main(int argc, char *argv[]) {
    create_window();
    return 0;
}

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
    
    // Multiplication and division first
    for (int i = 0; i < op_count; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            if (operators[i] == '*') {
                muldiv_lst[i] *= muldiv_lst[i + 1];
            } else if (operators[i] == '/') {
                if (muldiv_lst[i + 1] != 0) {
                    muldiv_lst[i] /= muldiv_lst[i + 1];
                } else {
                    printf("Error: Division by zero!\n");
                    return 0;
                }
            }
            // Shift elements
            for (int j = i + 1; j < num_count - 1; j++) {
                muldiv_lst[j] = muldiv_lst[j + 1];
            }
            num_count--;
            for (int j = i; j < op_count - 1; j++) {
                operators[j] = operators[j + 1];
            }
            op_count--;
            i--; // recheck same position
        }
    }
    
    // Handle addition and subtraction
    double result = muldiv_lst[0];
    for (int i = 0; i < op_count; i++) {
        if (operators[i] == '+') {
            result += muldiv_lst[i + 1];
        } else if (operators[i] == '-') {
            result -= muldiv_lst[i + 1];
        }
    }
    
    // Time end
    clock_t end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Result: %f\n", result);
    printf("Time: %f seconds\n", time_taken);
    return result;
}

// Callback function for the button click
void on_calculate_button_clicked(GtkWidget *widget, gpointer data) {
    const char *expression = gtk_entry_get_text(GTK_ENTRY(data));
    double result = calculate(expression);
    char result_text[MAX_EXPR_LEN];
    snprintf(result_text, sizeof(result_text), "Result: %.2f", result);
    gtk_label_set_text(GTK_LABEL(gtk_widget_get_parent(widget)), result_text);
}

// Function to create the main window
void create_window() {
    GtkWidget *window, *grid, *entry, *button, *label;

    gtk_init(NULL, NULL);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Calculate");
    g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_button_clicked), entry);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    label = gtk_label_new("Result: ");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    create_window();
    return 0;
}

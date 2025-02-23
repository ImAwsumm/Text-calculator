#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>

#define MAX_EXPR_LEN 256

// Global label pointer to update the result
GtkWidget *result_label;


//  ### Warning **This calculator is smarter than your phone's calculator because it's an awsum calculator and no other calculator is moAr awsum than mine**



// Function to process the input equation
double calculate(const char *equation) {
    // Arrays to store numbers and operators
    double numbers[MAX_EXPR_LEN];
    char operators[MAX_EXPR_LEN];
    int num_count = 0, op_count = 0;

    // Copy equation to avoid modifying the original input
    char eq[MAX_EXPR_LEN];
    strcpy(eq, equation);

    // Time start
    clock_t start = clock();

    // Tokenize the input string by spaces
    char *token = strtok(eq, " ");
    while (token != NULL) {
        // If the token is a number
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            numbers[num_count++] = atof(token); // Convert string to double and store
        }
        // If the token is an operator
        else if (strchr("+-*/", token[0]) != NULL) {
            operators[op_count++] = token[0]; // Store operator
        }
        token = strtok(NULL, " ");
    }

    // First pass: handle multiplication and division
    for (int i = 0; i < op_count; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            if (operators[i] == '*') {
                numbers[i] *= numbers[i + 1];
            } else if (operators[i] == '/') {
                if (numbers[i + 1] != 0) {
                    numbers[i] /= numbers[i + 1];
                } else {
                    printf("Error: Division by zero! Don't break my code you stupid battlenigth27!!\n");
                    return 0;
                }
            }

            // Shift elements after operation
            for (int j = i + 1; j < num_count - 1; j++) {
                numbers[j] = numbers[j + 1];
            }
            num_count--;

            // Shift operators
            for (int j = i; j < op_count - 1; j++) {
                operators[j] = operators[j + 1];
            }
            op_count--;
            i--; // Recheck the current position
        }
    }

    // Second pass: handle addition and subtraction
    double result = numbers[0];  // Start with the first number
    for (int i = 0; i < op_count; i++) {
        
        if (operators[i] == '+') {
            result += numbers[i + 1];  // Add the next number
        } else if (operators[i] == '-') {
            
            result -= numbers[i + 1];  // Subtract the next number
        }
    }

    // End the time
    clock_t end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Result: %f\n", result);
    printf("Time: %f seconds\n", time_taken);
        // // send the time in the terminal because you wanna flex how good your computer is :)
    
    return result;
}

// Callback function for the button click
void on_calculate_button_clicked(GtkWidget *widget, gpointer data) {
    const char *expression = gtk_entry_get_text(GTK_ENTRY(data));
    double result = calculate(expression);
    char result_text[MAX_EXPR_LEN];
    snprintf(result_text, sizeof(result_text), "Result: %.2f", result);
    gtk_label_set_text(GTK_LABEL(result_label), result_text);
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
    result_label = label;  // Store the label in a global variable
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    create_window();
    return 0;

    //It's all fixed now !! :)
}

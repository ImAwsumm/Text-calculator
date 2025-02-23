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

int main(int argc, char *argv[]) {
    create_window();
    return 0;
}

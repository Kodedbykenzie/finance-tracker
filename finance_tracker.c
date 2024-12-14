#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_CATEGORY_LENGTH 20
#define FILE_NAME "expenses.txt"

// Expense structure
typedef struct {
    char date[11];           // Format: YYYY-MM-DD
    char category[MAX_CATEGORY_LENGTH];
    float amount;
} Expense;

// Global array to store expenses
Expense expenses[MAX_EXPENSES];
int expense_count = 0;

// Function prototypes
void load_expenses();
void save_expenses();
void add_expense();
void view_expenses();
void generate_report();

int main() {
    int choice;

    // Load expenses from file
    load_expenses();

    // Main menu loop
    while (1) {
        printf("\n--- Personal Finance Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Generate Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_expense();
                break;
            case 2:
                view_expenses();
                break;
            case 3:
                generate_report();
                break;
            case 4:
                save_expenses();
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Load expenses from file
void load_expenses() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No previous expenses found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%10s %19s %f", expenses[expense_count].date, 
                  expenses[expense_count].category, 
                  &expenses[expense_count].amount) == 3) {
        expense_count++;
    }

    fclose(file);
    printf("Loaded %d expenses from file.\n", expense_count);
}

// Save expenses to file
void save_expenses() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error: Could not save expenses.\n");
        return;
    }

    for (int i = 0; i < expense_count; i++) {
        fprintf(file, "%s %s %.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }

    fclose(file);
    printf("Expenses saved successfully.\n");
}

// Add an expense
void add_expense() {
    if (expense_count >= MAX_EXPENSES) {
        printf("Error: Expense list is full.\n");
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", expenses[expense_count].date);
    printf("Enter category: ");
    scanf("%s", expenses[expense_count].category);
    printf("Enter amount: ");
    scanf("%f", &expenses[expense_count].amount);

    expense_count++;
    printf("Expense added successfully.\n");
}

// View all expenses
void view_expenses() {
    if (expense_count == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\n--- All Expenses ---\n");
    printf("%-10s %-15s %-10s\n", "Date", "Category", "Amount");
    for (int i = 0; i < expense_count; i++) {
        printf("%-10s %-15s $%.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}

// Generate report
void generate_report() {
    if (expense_count == 0) {
        printf("No expenses to report.\n");
        return;
    }

    float total = 0;
    float category_totals[MAX_EXPENSES] = {0};
    char categories[MAX_EXPENSES][MAX_CATEGORY_LENGTH];
    int unique_categories = 0;

    // Calculate totals
    for (int i = 0; i < expense_count; i++) {
        total += expenses[i].amount;

        // Check if category exists
        int category_index = -1;
        for (int j = 0; j < unique_categories; j++) {
            if (strcmp(categories[j], expenses[i].category) == 0) {
                category_index = j;
                break;
            }
        }

        // Add to category total
        if (category_index == -1) {
            strcpy(categories[unique_categories], expenses[i].category);
            category_totals[unique_categories] = expenses[i].amount;
            unique_categories++;
        } else {
            category_totals[category_index] += expenses[i].amount;
        }
    }

    // Display report
    printf("\n--- Expense Report ---\n");
    printf("Total Expenses: $%.2f\n", total);
    for (int i = 0; i < unique_categories; i++) {
        printf("%-15s: $%.2f\n", categories[i], category_totals[i]);
    }
}

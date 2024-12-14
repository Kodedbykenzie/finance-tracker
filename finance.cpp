#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure to store expense details
struct Expense {
    string date;
    string category;
    float amount;
};

// Globals
vector<Expense> expenses;
float savingsGoal = 0.0, currentSavings = 0.0;

// Function prototypes
bool validate_date(const string& date);
void add_expense();
void display_expenses();
void delete_expense();
void edit_expense();
void filter_expenses_by_date();
void generate_report();
void manage_savings();
void menu();

// Function to validate date format (YYYY-MM-DD)
bool validate_date(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    return true;
}

// Add a new expense
void add_expense() {
    Expense e;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> e.date;
    if (!validate_date(e.date)) {
        cout << "Invalid date format!\n";
        return;
    }
    cout << "Enter category: ";
    cin >> e.category;
    cout << "Enter amount: ";
    cin >> e.amount;
    if (e.amount < 0) {
        cout << "Amount cannot be negative!\n";
        return;
    }
    expenses.push_back(e);
    cout << "Expense added successfully!\n";
}

// Display all expenses
void display_expenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }
    cout << setw(12) << "Date" << setw(15) << "Category" << setw(10) << "Amount\n";
    cout << "---------------------------------------\n";
    for (const auto& e : expenses) {
        cout << setw(12) << e.date << setw(15) << e.category << setw(10) << fixed << setprecision(2) << e.amount << "\n";
    }
}

// Delete an expense
void delete_expense() {
    int index;
    display_expenses();
    if (expenses.empty()) return;

    cout << "Enter the expense number to delete (1 to " << expenses.size() << "): ";
    cin >> index;

    if (index < 1 || index > expenses.size()) {
        cout << "Invalid expense number!\n";
        return;
    }

    expenses.erase(expenses.begin() + index - 1);
    cout << "Expense deleted successfully!\n";
}

// Edit an expense
void edit_expense() {
    int index;
    display_expenses();
    if (expenses.empty()) return;

    cout << "Enter the expense number to edit (1 to " << expenses.size() << "): ";
    cin >> index;

    if (index < 1 || index > expenses.size()) {
        cout << "Invalid expense number!\n";
        return;
    }

    Expense& e = expenses[index - 1];
    cout << "Editing expense: " << setw(12) << e.date << setw(15) << e.category << setw(10) << e.amount << "\n";

    cout << "Enter new date (YYYY-MM-DD): ";
    cin >> e.date;
    if (!validate_date(e.date)) {
        cout << "Invalid date format. Edit canceled.\n";
        return;
    }

    cout << "Enter new category: ";
    cin >> e.category;

    cout << "Enter new amount: ";
    cin >> e.amount;
    if (e.amount < 0) {
        cout << "Amount cannot be negative. Edit canceled.\n";
        return;
    }

    cout << "Expense updated successfully!\n";
}

// Filter expenses by date range
void filter_expenses_by_date() {
    string start_date, end_date;
    cout << "Enter start date (YYYY-MM-DD): ";
    cin >> start_date;
    if (!validate_date(start_date)) {
        cout << "Invalid date format!\n";
        return;
    }

    cout << "Enter end date (YYYY-MM-DD): ";
    cin >> end_date;
    if (!validate_date(end_date)) {
        cout << "Invalid date format!\n";
        return;
    }

    cout << "\nFiltered expenses between " << start_date << " and " << end_date << ":\n";
    cout << setw(12) << "Date" << setw(15) << "Category" << setw(10) << "Amount\n";
    cout << "---------------------------------------\n";

    for (const auto& e : expenses) {
        if (e.date >= start_date && e.date <= end_date) {
            cout << setw(12) << e.date << setw(15) << e.category << setw(10) << fixed << setprecision(2) << e.amount << "\n";
        }
    }
}

// Generate a report
void generate_report() {
    if (expenses.empty()) {
        cout << "No expenses to report.\n";
        return;
    }

    float total_expenses = 0.0;
    cout << "\n--- Expense Report ---\n";

    for (const auto& e : expenses) {
        total_expenses += e.amount;
    }
    cout << "Total Expenses: $" << fixed << setprecision(2) << total_expenses << "\n";

    // Group expenses by category
    cout << "\nExpenses by Category:\n";
    vector<string> categories;
    for (const auto& e : expenses) {
        if (find(categories.begin(), categories.end(), e.category) == categories.end()) {
            categories.push_back(e.category);
            float category_total = 0.0;
            for (const auto& e2 : expenses) {
                if (e.category == e2.category) {
                    category_total += e2.amount;
                }
            }
            cout << e.category << ": $" << fixed << setprecision(2) << category_total << "\n";
        }
    }
}

// Savings goal
void manage_savings() {
    cout << "Your current savings: $" << fixed << setprecision(2) << currentSavings << "\n";
    cout << "Enter your savings goal: ";
    cin >> savingsGoal;

    char option;
    do {
        cout << "\nSavings Menu:\n";
        cout << "1. Add to Savings\n";
        cout << "2. View Progress\n";
        cout << "3. Exit Savings\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
        case '1': {
            float amount;
            cout << "Enter amount to add: ";
            cin >> amount;
            if (amount > 0) {
                currentSavings += amount;
                cout << "Savings updated. Current Savings: $" << fixed << setprecision(2) << currentSavings << "\n";
            } else {
                cout << "Amount must be positive!\n";
            }
            break;
        }
        case '2':
            cout << "Savings Goal: $" << fixed << setprecision(2) << savingsGoal << "\n";
            cout << "Current Savings: $" << fixed << setprecision(2) << currentSavings << "\n";
            cout << "Progress: " << (currentSavings / savingsGoal) * 100.0 << "%\n";
            break;
        case '3':
            cout << "Exiting Savings Menu.\n";
            break;
        default:
            cout << "Invalid option!\n";
        }
    } while (option != '3');
}

// Main menu
void menu() {
    char option;
    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Delete Expense\n";
        cout << "4. Edit Expense\n";
        cout << "5. Filter Expenses by Date\n";
        cout << "6. Generate Report\n";
        cout << "7. Manage Savings\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
        case '1': add_expense(); break;
        case '2': display_expenses(); break;
        case '3': delete_expense(); break;
        case '4': edit_expense(); break;
        case '5': filter_expenses_by_date(); break;
        case '6': generate_report(); break;
        case '7': manage_savings(); break;
        case '8': cout << "Exiting program.\n"; break;
        default: cout << "Invalid option! Try again.\n";
        }
    } while (option != '8');
}

// Main Function
int main() {
    menu();
    return 0;
}

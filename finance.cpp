#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

struct Expense {
    string name;
    float amount;
    string category;
    string date;
};

float savings_balance = 0.0f;
float savings_goal = 0.0f;

vector<Expense> expenses;

// Function to validate positive float numbers
bool validate_positive_float(float number) {
    return number > 0;
}

// Simple date format validation (YYYY-MM-DD)
bool validate_date(const string& date) {
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    return true;
}

// Add a new expense
void add_expense() {
    Expense new_expense;
    string amount_input;

    cout << "Enter expense name: ";
    cin.ignore();
    getline(cin, new_expense.name);

    // Get expense amount
    cout << "Enter expense amount: ";
    while (true) {
        getline(cin, amount_input);
        stringstream(amount_input) >> new_expense.amount;
        if (validate_positive_float(new_expense.amount)) break;
        else cout << "Please enter a valid positive number: ";
    }

    // Get expense category
    cout << "Enter expense category (e.g., food, transport): ";
    getline(cin, new_expense.category);

    // Get expense date
    cout << "Enter expense date (YYYY-MM-DD): ";
    while (true) {
        getline(cin, new_expense.date);
        if (validate_date(new_expense.date)) break;
        else cout << "Please enter a valid date in the format YYYY-MM-DD: ";
    }

    expenses.push_back(new_expense);
    cout << "Expense added successfully!" << endl;
}

// View the list of expenses
void view_expenses() {
    cout << "Expenses:\n";
    cout << "Name\tAmount\tCategory\tDate\n";
    for (const auto& e : expenses) {
        cout << e.name << "\t" << e.amount << "\t" << e.category << "\t" << e.date << endl;
    }
}

// Manage savings: set goal and add funds
void manage_savings() {
    string input;
    cout << "Current savings: " << savings_balance << endl;
    cout << "Enter your savings goal: ";
    while (true) {
        getline(cin, input);
        stringstream(input) >> savings_goal;
        if (validate_positive_float(savings_goal)) break;
        else cout << "Please enter a valid positive savings goal: ";
    }

    while (true) {
        cout << "Enter amount to add to savings (0 to stop): ";
        getline(cin, input);
        float amount_to_add;
        stringstream(input) >> amount_to_add;

        if (amount_to_add == 0) break;

        if (validate_positive_float(amount_to_add)) {
            savings_balance += amount_to_add;
            cout << "Amount added to savings. Current savings: " << savings_balance << endl;
        } else {
            cout << "Please enter a valid positive number." << endl;
        }
    }
}

// Generate a financial report
void generate_report() {
    cout << "\nGenerating report...\n";
    float total_expenses = 0;
    for (const auto& e : expenses) {
        total_expenses += e.amount;
    }
    cout << "Total Expenses: " << total_expenses << endl;
    cout << "Total Savings: " << savings_balance << endl;
    cout << "Savings Goal: " << savings_goal << endl;

    if (savings_balance >= savings_goal) {
        cout << "Congratulations! You've reached your savings goal." << endl;
    } else {
        cout << "You are " << savings_goal - savings_balance << " away from reaching your savings goal." << endl;
    }
}

// Main function to drive the menu
int main() {
    int choice;
    do {
        cout << "\nPersonal Finance Tracker\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Manage Savings\n";
        cout << "4. Generate Report\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add_expense(); break;
            case 2: view_expenses(); break;
            case 3: manage_savings(); break;
            case 4: generate_report(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 5);

    return 0;
}

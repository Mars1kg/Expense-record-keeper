#include <iostream>
#include <vector>

using namespace std;

struct Transaction {
    string date, category, description;
    double amount;
};

struct TransactionManager {
    vector<Transaction> transactions;

    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
    }

    void deleteTransaction(int index) {
        if (index >= 0 && index < transactions.size()) {
            transactions.erase(transactions.begin() + index);
            cout << "Transaction deleted.\n";
        } else {
            cout << "Invalid transaction index.\n";
        }
    }

    void generateReport() const {
        double balance = 0.0;
        cout << "Transaction Report:\n";
        for (size_t i = 0; i < transactions.size(); ++i) {
            const auto& transaction = transactions[i];
            cout << "Date: " << transaction.date << "\n";
            cout << "Amount: с" << transaction.amount << "\n";
            cout << "Category: " << transaction.category << "\n";
            cout << "Description: " << transaction.description << "\n\n";
            balance += transaction.amount;
        }
        cout << "Balance: с" << balance << "\n";
    }
};

int main() {
    TransactionManager manager;

    int choice;
    do {
        cout << "\nTransaction Manager\n";
        cout << "1. Add Expense\n";
        cout << "2. Add Income\n";
        cout << "3. Delete Transaction\n";
        cout << "4. Generate Report\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            case 2: {
                Transaction transaction;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> transaction.date;
                cout << "Enter amount: ";
                cin >> transaction.amount;
                cout << "Enter category: ";
                cin >> transaction.category;
                cout << "Enter description: ";
                cin.ignore();
                getline(cin, transaction.description);
                if (choice == 1) transaction.amount = -transaction.amount;
                manager.addTransaction(transaction);
                cout << "Transaction added.\n";
                break;
            }
            case 3: {
                int index;
                cout << "Enter index of transaction to delete: ";
                cin >> index;
                manager.deleteTransaction(index);
                break;
            }
            case 4:
                manager.generateReport();
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

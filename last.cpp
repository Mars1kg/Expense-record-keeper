#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

struct Transaction {
    string date, category, description;
    double amount;
};

class TransactionManager {
public:
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
        for (const auto& transaction : transactions) {
            cout << "Date: " << transaction.date << "\n";
            cout << "Amount: $" << transaction.amount << "\n";
            cout << "Category: " << transaction.category << "\n";
            cout << "Description: " << transaction.description << "\n\n";
            balance += transaction.amount;
        }
        cout << "Balance: $" << balance << "\n";
    }
};

void saveTransactionsToFile(const TransactionManager& manager, const string& filename) {
    ofstream file(filename);
    if (file) {
        for (const auto& transaction : manager.transactions) {
            file << transaction.date << "," << transaction.amount << ","
                 << transaction.category << "," << transaction.description << "\n";
        }
        cout << "Transactions saved to file.\n";
    } else {
        cout << "Failed to open file for writing.\n";
    }
}

TransactionManager loadTransactionsFromFile(const string& filename) {
    TransactionManager manager;
    ifstream file(filename);
    if (file) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Transaction transaction;
            char delimiter;
            ss >> transaction.date >> delimiter >> transaction.amount >> delimiter
               >> transaction.category;
            getline(ss, transaction.description);
            manager.addTransaction(transaction);
        }
        cout << "Transactions loaded from file.\n";
    } else {
        cout << "Failed to open file for reading.\n";
    }
    return manager;
}

int main() {
    TransactionManager manager = loadTransactionsFromFile("transactions.dat");

    int choice;
    do {
        cout << "\nTransaction Manager\n";
        cout << "1. Add Expense\n";
        cout << "2. Add Income\n";
        cout << "3. Delete Transaction\n";
        cout << "4. Generate Report\n";
        cout << "5. Save and Exit\n";
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
            case 5:
                saveTransactionsToFile(manager, "transactions.dat");
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

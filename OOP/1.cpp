#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;
    vector<string> transactionHistory;

public:
    Account(string accNum, string accHolder, double initialBalance)
        : accountNumber(accNum), accountHolderName(accHolder), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back("Deposited " + to_string(amount) + ", New Balance: " + to_string(balance));
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            transactionHistory.push_back("Withdrew " + to_string(amount) + ", New Balance: " + to_string(balance));
        } else {
            cout << "Insufficient balance or invalid amount." << endl;
        }
    }

    void displayAccountDetails() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
        cout << "Transaction History: " << endl;
        for (const auto& transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string accHolder, double initialBalance, double rate)
        : Account(accNum, accHolder, initialBalance), interestRate(rate) {}

    void calculateInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
        transactionHistory.push_back("Interest Added: " + to_string(interest) + ", New Balance: " + to_string(balance));
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(string accNum, string accHolder, double initialBalance, double limit)
        : Account(accNum, accHolder, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            transactionHistory.push_back("Withdrew " + to_string(amount) + ", New Balance: " + to_string(balance));
        } else {
            cout << "Overdraft limit exceeded or invalid amount." << endl;
        }
    }
};

int main() {
    SavingsAccount savings("SA123", "John Doe", 1000, 5);
    CurrentAccount current("CA123", "Jane Doe", 2000, 500);

    savings.deposit(500);
    savings.withdraw(200);
    savings.calculateInterest();
    savings.displayAccountDetails();

    cout << endl;

    current.deposit(1000);
    current.withdraw(2500);
    current.withdraw(500);
    current.displayAccountDetails();

    return 0;
}

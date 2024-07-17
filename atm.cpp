#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Account {
private:
    int balance;

public:
    Account(int initialBalance = 0) : balance(initialBalance) {}

    int getBalance() const {
        return balance;
    }

    void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class Customer {
private:
    string cardNumber;
    int pinNumber;

public:
    Customer(const string& card, int pin) : cardNumber(card), pinNumber(pin) {}

    const string& getCardNumber() const {
        return cardNumber;
    }

    int getPIN() const {
        return pinNumber;
    }
};

class ATM {
private:
    unordered_map<string, Account> accounts;
    vector<Customer> customers;
    Customer currentCustomer;
    bool isAuthenticated;

public:
    ATM() : currentCustomer("", 0), isAuthenticated(false) {}

    void addCustomer(const string& cardNumber, int pinNumber) {
        customers.push_back(Customer(cardNumber, pinNumber));
    }

    void insertCard(const string& cardNumber, int pinNumber) {
        for (const Customer& customer : customers) {
            if (customer.getCardNumber() == cardNumber && customer.getPIN() == pinNumber) {
                currentCustomer = customer;
                isAuthenticated = true;
                return;
            }
        }
        isAuthenticated = false;
    }

    bool isCardRegistered(const string& cardNumber) const {
        for (const Customer& customer : customers) {
            if (customer.getCardNumber() == cardNumber) {
                return true;
            }
        }
        return false;
    }

    bool selectAccount() {
        if (isAuthenticated) {
            accounts[currentCustomer.getCardNumber()] = Account();
            return true;
        }
        return false;
    }

    int checkBalance() const {
        if (isAuthenticated && accounts.find(currentCustomer.getCardNumber()) != accounts.end()) {
            return accounts.at(currentCustomer.getCardNumber()).getBalance();
        }
        return 0;
    }

    void deposit(int amount) {
        if (isAuthenticated && accounts.find(currentCustomer.getCardNumber()) != accounts.end()) {
            accounts[currentCustomer.getCardNumber()].deposit(amount);
            cout << amount << " deposited successfully." << endl;
        } else {
            cout << "Failed to deposit." << endl;
        }
    }

    void withdraw(int amount) {
        if (isAuthenticated && accounts.find(currentCustomer.getCardNumber()) != accounts.end()) {
            if (accounts[currentCustomer.getCardNumber()].withdraw(amount)) {
                cout << amount << " withdrawn successfully." << endl;
            } else {
                cout << "Insufficient funds." << endl;
            }
        } else {
            cout << "Failed to withdraw." << endl;
        }
    }
};

void testInsertCardAndSelectAccount(ATM& atm) {
    cout << "[Test Case 1: Inserting card and selecting account]" << endl;
    atm.insertCard("1234", 5678);
    if (atm.selectAccount()) {
        cout << "Account selected." << endl;
        int balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;

        atm.deposit(100);
        balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;

        atm.withdraw(50);
        balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;
    } else {
        cout << "Invalid card number or PIN." << endl;
    }
    cout << endl;
}

void testInsertCardWithInvalidPIN(ATM& atm) {
    cout << "[Test Case 2: Inserting card with invalid PIN]" << endl;
    atm.insertCard("1234", 9999);
    if (atm.selectAccount()) {
        cout << "Account selected." << endl;
        int balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;
    } else {
        cout << "Invalid card number or PIN." << endl;
    }
    cout << endl;
}

void testInsertUnregisteredCard(ATM& atm) {
    cout << "[Test Case 3: Inserting unregistered card]" << endl;
    atm.insertCard("9999", 1234);
    if (atm.selectAccount()) {
        cout << "Account selected." << endl;
        int balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;
    } else {
        cout << "Invalid card number or PIN." << endl;
    }
    cout << endl;
}

void testDeposit(ATM& atm) {
    cout << "[Test Case 4: Depositing money]" << endl;
    atm.insertCard("1234", 5678);
    if (atm.selectAccount()) {
        atm.deposit(200);
        int balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;
    } else {
        cout << "Invalid card number or PIN." << endl;
    }
    cout << endl;
}

void testWithdraw(ATM& atm) {
    cout << "[Test Case 5: Withdrawing money]" << endl;
    atm.insertCard("5678", 1234);
    if (atm.selectAccount()) {
        atm.withdraw(50);
        int balance = atm.checkBalance();
        cout << "Current Balance= $" << balance << endl;
    } else {
        cout << "Invalid card number or PIN." << endl;
    }
    cout << endl;
}

int main() {
    ATM atm;

    atm.addCustomer("1234", 5678);
    atm.addCustomer("5678", 1234);

    testInsertCardAndSelectAccount(atm);
    testInsertCardWithInvalidPIN(atm);
    testInsertUnregisteredCard(atm);
    testDeposit(atm);
    testWithdraw(atm);

    return 0;
}


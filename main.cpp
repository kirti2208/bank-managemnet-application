#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class BankAccount {
public:
    int accNo;
    string name;
    float balance;
};

void createAccount() {
    BankAccount a;

    cout << "\nEnter Account Number: ";
    cin >> a.accNo;

    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, a.name);

    cout << "Enter Initial Balance: ";
    cin >> a.balance;

    ofstream file("accounts.txt", ios::app);

    file << a.accNo << "|"
         << a.name << "|"
         << a.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    ifstream file("accounts.txt");

    string line;

    cout << "\n===== ACCOUNT DETAILS =====\n";

    while (getline(file, line)) {
        stringstream ss(line);

        string accNo, name, balance;

        getline(ss, accNo, '|');
        getline(ss, name, '|');
        getline(ss, balance);

        cout << "\nAccount No : " << accNo;
        cout << "\nName       : " << name;
        cout << "\nBalance    : Rs. " << balance;
        cout << "\n-------------------------";
    }

    file.close();
}

void checkBalance() {
    int accountNo;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    ifstream file("accounts.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string accNo, name, balance;

        getline(ss, accNo, '|');
        getline(ss, name, '|');
        getline(ss, balance);

        if (stoi(accNo) == accountNo) {
            cout << "\nAccount Holder : " << name;
            cout << "\nCurrent Balance : Rs. " << balance << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

void depositMoney() {
    int accountNo;
    float amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string accNo, name, balance;

        getline(ss, accNo, '|');
        getline(ss, name, '|');
        getline(ss, balance);

        float bal = stof(balance);

        if (stoi(accNo) == accountNo) {
            bal += amount;

            temp << accNo << "|"
                 << name << "|"
                 << bal << endl;

            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "\nAmount Deposited Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

void withdrawMoney() {
    int accountNo;
    float amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string accNo, name, balance;

        getline(ss, accNo, '|');
        getline(ss, name, '|');
        getline(ss, balance);

        float bal = stof(balance);

        if (stoi(accNo) == accountNo) {

            if (bal >= amount) {
                bal -= amount;

                temp << accNo << "|"
                     << name << "|"
                     << bal << endl;

                cout << "\nWithdrawal Successful!\n";
            }
            else {
                temp << line << endl;
                cout << "\nInsufficient Balance!\n";
            }

            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main() {

    int choice;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            createAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            checkBalance();
            break;

        case 5:
            displayAccounts();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while(choice != 6);

    return 0;
}
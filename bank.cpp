//
// Anthony Luong and Leonardo Mota-Villaraldo on 03/03/2020
//
#include "bank.h"
#include <sstream>

// Takes in a file name as a param and begins processing the transactions.
Bank::Bank(const string& fileName) { processTransactions(fileName); }
// Default constructor.
Bank::Bank() = default;
// Default constructor.
Bank::~Bank() = default;

ostream& operator<<(ostream& os, const Bank& bank) {
    os << bank.accounts;
    return os;
}

// Reads files and builds line by line queue for FIFO processing
void Bank::processTransactions(const string& fileName) {
    ifstream inStream;
    inStream.open(fileName);
    string readLine;
    if (!inStream) {
        cout << "ERROR: No File Found Matching :" << fileName;
        return;
    }

    while (!inStream.eof()) {
        getline(inStream, readLine);
        // occurs when we've reached the end of the txt file
        if (readLine.empty()) {
            break;
        }
        transaction.push(readLine);
    }
    inStream.close();

    // While we still have transactions, do them.
    while (!transaction.empty()) {
        // Parsing the First line in queue
        parseString(transaction.front());
        // Remove the line from the queue.
        transaction.pop();
    }
}

// Returns true if acc exists within the AccountTree of this bank.
bool Bank::accountExists(Account* acc) {
    return accounts.retrieve(acc->getAccountNumber(), acc);
}

// Returns true if the account number of the account to be opened does not exist
// and is opened successfully. Returns false other wise.
bool Bank::openAccount(const string& firstName, const string& lastName,
                       int accNum) {
    // Create a new Account using the account number, first name, and last name.
    auto* newAcc = new Account(accNum, firstName, lastName);
    // Check if there is an account with same account number.
    if (accountExists(newAcc)) {
        // Delete the allocated memory since the account already exists.
        delete newAcc;
        cout << "ERROR: Account " << accNum
             << " is already open. Transaction refused." << endl;
        return false;
    }
    if (!accounts.insert(newAcc)) {
        delete newAcc;
        return false;
    }
    return true;
}

// Returns true if money is withdrawn successfully, other wise return false.
bool Bank::withdrawAssets(int accNum, int fund, int amt) {
    Account* acc = nullptr;
    accounts.retrieve(accNum, acc);
    if (acc == nullptr) {
        cout << "ERROR: Could not find Account " << accNum
             << " Withdraw cancelled." << endl;
        return false;
    }
    return acc->withdraw(fund, amt);
}

// Returns true if transfer between accounts is successful, other wise return
// false.
bool Bank::transferAssets(int accNum1, int transferAmount, int fundType1,
                          int fundType2, int accNum2) {
    Account* acc = nullptr;
    accounts.retrieve(accNum1, acc);
    Account* acc2 = nullptr;
    accounts.retrieve(accNum2, acc2);
    if (acc == nullptr || acc2 == nullptr) {
        cout << "ERROR: Could not find Account "
             << (acc == nullptr ? accNum1 : accNum2) << " Transfer cancelled."
             << endl;
        return false;
    }
    return acc->transfer(acc2, fundType1, fundType2, transferAmount);
}

// Returns true if depositing was successful, otherwise false.
bool Bank::depositAssets(int accNum, int fund, int amt) {
    Account* acc = nullptr;
    accounts.retrieve(accNum, acc);
    if (acc == nullptr) {
        cout << "ERROR: Could not find Account " << accNum
             << " Deposit cancelled." << endl;
        return false;
    }
    return acc->deposit(fund, amt);
}

// Displays all the history of the given account number.
void Bank::historyTransaction(int accNum, int fundType) {
    Account* acc = nullptr;
    accounts.retrieve(accNum, acc);
    if (acc == nullptr) {
        cout << "ERROR: Could not find Account " << accNum
             << " History cancelled." << endl;
        return;
    }
    acc->getHistory(fundType);
}

// Displays total balances for every account in the account tree of this bank.
void Bank::displayAllBankBalances() const {
    cout << "\nProcessing Done. Final Balances." << endl;
    accounts.display();
}

// Returns true if string was successfully parsed, other wise returns false.
bool Bank::parseString(const string& line) {
    // store the line paramaters. Never more than 4 params
    string params[4];
    int i = 0;
    stringstream tmpLine(line);
    // 'split' array by " "
    while (tmpLine.good() && i < 6) {
        tmpLine >> params[i];
        ++i;
    }

    string operation = params[0];
    // check if it is a valid char, if not it is invalid syntax
    if (operation == "O") {
        // params = [Operation, firstName, lastName, accountNumber]
        string firstName = params[1];
        string lastName = params[2];
        // cast the string account number into an int.
        int accountNumber = stoi(params[3]);
        // We cannot open an account with more than 4 characters.
        if (accountNumber > 9999) {
            cout << "ERROR: Account " + to_string(accountNumber) +
                        " is not within bounds. Transaction refused.";
            return false;
        }
        return openAccount(firstName, lastName, accountNumber);
        // W and D have the same params, the only difference is function
        // calling.
    }
    if (operation == "W" || operation == "D") {
        // params = [Operation, accountNumber, amount]
        int accountNumber = stoi(params[1]); // add try catch later
        int moneyValue = stoi(params[2]);    // add try catch later

        // Account number should include a fifth digit dictating which fund type
        // is the target. If it is more than 5 digits, or less than 4 digits it
        // is invalid syntax.
        if (accountNumber > 99999 || accountNumber < 10000) {
            cout << "ERROR: Account number must have a fifth digit for target "
                    "fund type. Transaction refused."
                 << endl;
            return false;
        }
        //  Mod 10 gives the last digit, which has to be the fundType.
        int fundType = accountNumber % 10;
        // Remove the last digit to ensure the account can be found if it
        // exists.
        accountNumber /= 10;

        if (operation == "W") {
            return withdrawAssets(accountNumber, fundType, moneyValue);
        }

        // If it wasn't withdraw it has to be deposit.
        return depositAssets(accountNumber, fundType, moneyValue);
    }
    if (operation == "H") {
        // params = [operation, accountNumber]
        int accountNumber = stoi(params[1]);
        // account number can only be 4 or 5 digits, nothing less nothing more.
        if (accountNumber < 1000 || accountNumber > 99999) {
            cout << "ERROR: Account number length is either too short or too "
                    "long."
                 << endl;
            return false;
        }

        int fundType = -1;
        // Because you can call history on a specific fund type we should
        // extract it. But only if account number has a fifth digit.
        if (accountNumber > 9999) {
            // get last digit.
            fundType = accountNumber % 10;
            // remove the last digit.
            accountNumber /= 10;
            // print only the fund type
        }

        historyTransaction(accountNumber, fundType);
        return true;
    }
    if (operation == "T") {
        // params = [operation, accountNumber1, amount, accountNumber2]
        int accountNumber1 = stoi(params[1]);
        int accountNumber2 = stoi(params[3]);
        int transferAmount = stoi(params[2]);

        // if we have more than 5 digits on either account number, it is invalid
        // syntax.
        if (accountNumber1 > 99999 || accountNumber2 > 99999) {
            cout << "ERROR: Account number length is either too short or too "
                    "long."
                 << endl;
            return false;
        }

        // get last digit of account 1
        int fundType1 = accountNumber1 % 10;
        // get last digit of account 2
        int fundType2 = accountNumber2 % 10;

        // Remove the last digit from both accounts.
        accountNumber1 /= 10;
        accountNumber2 /= 10;
        return transferAssets(accountNumber1, transferAmount, fundType1,
                              fundType2, accountNumber2);
    }

    return false;
}

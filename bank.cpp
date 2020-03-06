//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//
#include "bank.h"
#include <sstream>

// Takes in a file name as a param and begins processing the transactions.
Bank::Bank(string fileName) { processTransactions(fileName); }
// Default constructor.
Bank::Bank() {}
// Default constructor.
Bank::~Bank() = default;

// Reads files and builds line by line queue for FIFO processing
void Bank::processTransactions(const string& fileName) {
    ifstream inStream;
    inStream.open(fileName);
    string readLine = "";
    if (!inStream) {
        cout << "ERROR: No File Found Matching :" << fileName;
        return;
    }

    while (!inStream.eof()) {
        getline(inStream, readLine);
        // occurs when we've reached the end of the txt file
        if (readLine == "") {
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
bool Bank::openAccount(string firstName, string lastName, int accNum) {
    // Create a new Account using the account number, first name, and last name.
    Account* newAcc = new Account(accNum, firstName, lastName);
    // Check if there is an account with same account number.
    if (accountExists(newAcc)) {
        // Delete the allocated memory since the account already exists.
        delete newAcc;
        cout << "ERROR: Account " << accNum
             << "is already open. Transaction refused." << endl;
        return false;
    }
    accounts.insert(newAcc);
    return true;
}

// Returns true if money is withdrawn successfully, other wise return false.
bool Bank::withdrawAssets(int accNum, int fund, int amt) {
    Account* acc;
    accounts.retrieve(accNum, acc);
    return acc->withdraw(fund, amt);
}

// Returns true if transfer between accounts is successful, other wise return
// false.
bool Bank::transferAssets(int accNum1, int transferAmount, int fundType1,
                          int fundType2, int accNum2) {
    Account* acc;
    accounts.retrieve(accNum1, acc);
    Account* acc2;
    accounts.retrieve(accNum2, acc2);
    return acc->transfer(acc2, fundType1, fundType2, transferAmount);
}

// Returns true if depositing was successful, otherwise false.
bool Bank::depositAssets(int accNum, int amt, int fund) {
    Account* acc;
    accounts.retrieve(accNum, acc);
    return acc->deposit(fund, amt);
}

// Displays all the history of the given account number.
void Bank::historyTransaction(int accNum) {
    Account* acc;
    accounts.retrieve(accNum, acc);
    acc->getHistory();
}

// Displays total balances for every account in the account tree of this bank.
void Bank::displayAllBankBalances() const { accounts.display(); }

// Returns true if string was successfully parsed, other wise returns false.
bool Bank::parseString(string line) {
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
            throw "ERROR: Account " + to_string(accountNumber) +
                " is not within bounds. Transaction refused.";
            return false;
        }
        return openAccount(firstName, lastName, accountNumber);
        // W and D have the same params, the only difference is function
        // calling.
    } else if (operation == "W" || operation == "D") {
        // params = [Operation, accountNumber, amount]
        int accountNumber = stoi(params[1]); // add try catch later
        int moneyValue = stoi(params[2]);    // add try catch later

        // Account number should include a fifth digit dictating which fund type
        // is the target. If it is more than 5 digits, or less than 4 digits it
        // is invalid syntax.
        if (accountNumber > 99999 || accountNumber < 10000) {
            throw "err";
            return false;
        }
        //  Mod 10 gives the last digit, which has to be the fundType.
        int fundType = accountNumber % 10;
        // Remove the last digit to ensure the account can be found if it
        // exists.
        accountNumber /= 10;
        Account* acc;
        accounts.retrieve(accountNumber, acc);
        if (acc == nullptr) {
            throw "err";
            return false;
        }

        if (operation == "W") {
            return acc->withdraw(fundType, moneyValue);
        }

        // If it wasn't withdraw it has to be deposit.
        return acc->deposit(fundType, moneyValue);
    } else if (operation == "H") {
        // params = [operation, accountNumber]
        int accountNumber = stoi(params[1]);
        // account number can only be 4 or 5 digits, nothing less nothing more.
        if (accountNumber < 1000 && accountNumber > 99999) {
            throw "err";
            return false;
        }

        int fundType;
        // Because you can call history on a specific fund type we should
        // extract it. But only if account number has a fifth digit.
        if (accountNumber > 9999) {
            // get last digit.
            fundType = accountNumber % 10;
            // remove the last digit.
            accountNumber /= 10;
            // print only the fund type
        }

        Account* acc;
        accounts.retrieve(accountNumber, acc);
        if (acc == nullptr) {
            throw "err";
            return false;
        }
        acc->getHistory();
        return true;
    } else if (operation == "T") {
        // params = [operation, accountNumber1, amount, accountNumber2]
        int accountNumber1 = stoi(params[1]);
        int accountNumber2 = stoi(params[3]);
        int transferAmount = stoi(params[2]);

        // if we have more than 5 digits on either account number, it is invalid
        // syntax.
        if (accountNumber1 > 99999 || accountNumber2 > 99999) {
            throw "err";
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

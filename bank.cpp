//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//
#include <sstream>
#include "bank.h"

// empty

Bank::Bank(string fileName) {}

Bank::~Bank() = default;

// reads files and builds line by line queue for FIFO processing
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

    while (!transaction.empty()) {
        char transactionChar = transaction.front()[0];
        string firstName; // get first name from line
        string lastName; // get first name from line
        int accNum; // get first name from line
        // string processing = transaction.front().substr(2);
        switch (transactionChar) {
        case 'O':
            openAccount(firstName, lastName, accNum);
            break;
        case 'W':
            //withdrawAssets
            break;
        case 'T':
            //transferAssets
            break;
        case 'D':
            //depositAssets
            break;
        case 'H':
            //historyTransaction
            break;
        default:
            cout << "ERROR: Invalid transaction type." << endl;
        }
        transaction.pop();
    }
}

bool Bank::openAccount(string firstName, string lastName, int accNum) {
    Account* newAcc = new Account(accNum, firstName, lastName);
    if (accountExists(newAcc)) {
        delete newAcc;
        cout << "ERROR: Account " << accNum << "is already open. Transaction refused." << endl;
        return false;
    }
    accounts.insert(newAcc);
    return true;
}

bool Bank::withdrawAssets(int accNum, int fund, int amt) {
    Account* acc = accounts.getAccount(accNum);
    return acc->withdraw(fund, amt);
}

bool Bank::transferAssets(int accNum1, int transferAmount, int fundType, int accNum2) {
    Account* acc = accounts.getAccount(accNum1);
    Account* acc2 = accounts.getAccount(accNum2);
    return acc->transfer(*acc2, fundType, transferAmount);
}

bool Bank::depositAssets(int accNum, int amt, int fund) {
    Account* acc = accounts.getAccount(accNum);
    return acc->deposit(fund, amt);
}

void Bank::historyTransaction(int accNum) {

}

void Bank::displayAllBankBalances() const {
}

bool Bank::parseString(string line) const {
    
}
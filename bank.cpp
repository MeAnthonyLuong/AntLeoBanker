//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//
#include <sstream>
#include "bank.h"

// empty

Bank::Bank(string fileName) { processTransactions(fileName); }
Bank::Bank() {}
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
        parseString(transaction.front());
        transaction.pop();
  }   
}

bool Bank::accountExists(Account* acc) {
    return false;
}

bool Bank::openAccount(string firstName, string lastName, int accNum)  {
    Account* newAcc = new Account(accNum, firstName, lastName);
    if (accountExists(newAcc)) {
        delete newAcc;
        cout << "ERROR: Account " << accNum << "is already open. Transaction refused." << endl;
        return false;
    }
    accounts.insert(newAcc);
    return true;
}

bool Bank::withdrawAssets(int accNum, int fund, int amt)  {
    Account* acc;
    accounts.retrieve(accNum, acc);
    return acc->withdraw(fund, amt);
}

bool Bank::transferAssets(int accNum1, int transferAmount, int fundType, int accNum2)  {
    Account* acc;
    accounts.retrieve(accNum1, acc);
    Account* acc2;
    accounts.retrieve(accNum2, acc2);
    return acc->transfer(*acc2, fundType, transferAmount);
}

bool Bank::depositAssets(int accNum, int amt, int fund)  {
    Account* acc;
    accounts.retrieve(accNum, acc);
    return acc->deposit(fund, amt);
}

void Bank::historyTransaction(int accNum)  {

}

void Bank::displayAllBankBalances()  const {
    accounts.display();
}

bool Bank::parseString(string line)  {
    // store the line paramaters. Never more than 4 params
    string params[4];
    int i = 0;
    stringstream tmpLine(line);
    // split array by " "
    while (tmpLine.good() && i < 6) {
        tmpLine >> params[i];
        ++i;
    }

    string operation = params[0];
    // check if it is a char, if not it is invalid syntax
    if (operation == "O") {
        string firstName = params[1];
        string lastName = params[2];
        int accountNumber = stoi(params[3]);
        // We cannot open an account with more than 4 characters.
        if (accountNumber > 9999) {
            throw "err";
        }

        return openAccount(firstName, lastName, accountNumber);
    } else if (operation == "W" || operation == "D") {
        int accountNumber = stoi(params[1]); //add try catch later
        int moneyValue = stoi(params[2]); //add try catch later
        
        if (accountNumber > 99999 && accountNumber < 10000) {
            throw "err";
        }
        // extract the parameters
        // if operation == w call withdraw else call deposit
    } else if (operation == "H") {
        int accountNumber = stoi(params[1]);
        if (accountNumber < 1000 && accountNumber > 99999) {
            throw "err";
        }
        //print history depending on the length

    } else if (operation == "T") {
        int accountNumber1 = stoi(params[1]);
        int accountNumber2 = stoi(params[3]);
        int transferAmount = stoi(params[2]);
        if(accountNumber1 > 99999 || accountNumber2 > 99999) {
            throw "err";
        }
        // add giver and receiver
        transferAssets(accountNumber1, transferAmount, 1,
                       accountNumber2);
    }
}
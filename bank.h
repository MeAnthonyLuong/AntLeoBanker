//
// Anthony Luong and Leonardo Mota-Villaraldo on 03/03/2020
//

#pragma once

#include "accounttree.h"
#include <fstream>
#include <queue>
#include <string>

using namespace std;

class Bank {
    friend ostream& operator<<(ostream& os, const Bank& bank);

  public:
    // Constructor with input file.
    explicit Bank(const string& fileName);
    // Default constructor
    Bank();
    // Destructor
    ~Bank();

    // Function that parses a line of transaction.
    bool parseString(const string& line);

    // Processes the transactions of a file.
    void processTransactions(const string& fileName);
    // Displays total balances for every account in the bank.
    void displayAllBankBalances() const;

    // Opens an account.
    bool openAccount(const string& firstName, const string& lastName,
                     int accNum);
    // Withdraws money from an account.
    bool withdrawAssets(int accNum, int fund, int amt);
    // Transfers money between accounts.
    bool transferAssets(int accNum1, int transferAmount, int fundType1,
                        int fundType2, int accNum2);
    // Deposits money into an account.
    bool depositAssets(int accNum, int fund, int amt);
    // Displays history of an account.
    void historyTransaction(int accNum, int fundType = -1);

  private:
    // inserts an account into the account tree.
    bool insertAccounts(Account* acc);
    // checks if an account exists.
    bool accountExists(Account* acc);
    AccountTree accounts;
    queue<string> transaction;
};

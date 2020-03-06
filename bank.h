//
// Anthony Luong and Leonardo Mota-Villaraldo on 03/03/2020
//

#pragma once

#include "accounttree.h"
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class Bank {
  friend ostream& operator<<(ostream& os, Bank& bank);
  public:
    Bank(string inputFile);
    Bank();
    ~Bank();

    bool parseString(string line);
    
    void processTransactions(const string& fileName);
    void displayAllBankBalances() const;

    
    bool openAccount(string firstName, string lastName, int accNum);
    bool withdrawAssets(int accNum, int fund, int amt);
    bool transferAssets(int accNum1, int transferAmount, int fundType, int accNum2);
    bool depositAssets(int accNum, int amt, int fund);
    void historyTransaction(int accNum);
    // test

  private:
    bool insertAccounts(Account* acc);
    bool accountExists(Account* acc);
    AccountTree accounts;
    queue<string> transaction;
};

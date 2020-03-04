//
// Created by <Name> on <Date>.
//

#pragma once

#include "accounttree.h"
#include <fstream>
#include <string>

using namespace std;

class Bank {
  public:
    Bank();
    ~Bank();

    void processTransactions(const string& fileName);
    void displayAllBankBalances() const;

  private:
    AccountTree accounts;
};

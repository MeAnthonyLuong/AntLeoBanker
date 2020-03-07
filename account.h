//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#pragma once

#include "funds.h"
#include <deque>
#include <iostream>
#include <string>

using namespace std;

class Account {
    // Displays acount information.
    friend ostream& operator<<(ostream& os, const Account& acc);

  public:
    // Account constructor that takes in a 4 digit account number, first name,
    // and last name.
    Account(int accNum, const string firstName, const string lastName);
    // Destructor
    ~Account();
    // withdraws money from a specified fund type.
    bool withdraw(int fundType, int amt);
    // deposits money into a specified fund type.
    bool deposit(int fundType, int amt);
    // transfers money from one fund type to another fund type.
    bool transfer(Account* otherAcc, int fundType1, int fundType2, int amt);
    // displays a history of transactions.
    void getHistory(int fundType = -1);
    // returns the account number.
    int getAccountNumber() const;

  private:
    // private variable of all fund types
    const string fundNames[10] = {"Money Market",       "Prime Money Market",
                              "Long-Term Bond",     "Short-Term Bond",
                              "500 Index Fund",     "Capital Value Fund",
                              "Growth Equity Fund", "Growth Index Fund",
                              "Value Fund",         "Value Stock Index"};
    // Double ended queue containing history log of transactions.
    Funds history[10];
    // Max amount of fund types allowed.
    const static int MAX_ACC = 10;
    // A four digit account number.
    int accNum;
    // Holds the amount of money in a fund type.
    int funds[MAX_ACC] = {0};
    string firstName;
    string lastName;
};

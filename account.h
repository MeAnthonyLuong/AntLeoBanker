//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#pragma once

#include <deque>
#include <iostream>
#include <string>

using namespace std;


class Account {
    friend ostream& operator<<(ostream& os, const Account& acc);

  public:
    Account(int accNum, string firstName, string lastName);
    ~Account();
    bool withdraw(int fundType, int amt);
    bool deposit(int fundType, int amt);
    bool transfer(Account* otherAcc, int fundType1, int fundType2, int amt);
    void getHistory(int fundType = -1);
    int getAccountNumber() const;

  private:
    const string FUNDS[10] = {"Money Market",       "Prime Money Market",
                              "Long-Term Bond",     "Short-Term Bond",
                              "500 Index Fund",     "Capital Value Fund",
                              "Growth Equity Fund", "Growth Index Fund",
                              "Value Fund",         "Value Stock Index"};
    deque<string> history;
    const static int MAX_ACC = 10;
    int accNum;

    int funds[MAX_ACC] = {0};
    string firstName;
    string lastName;
};

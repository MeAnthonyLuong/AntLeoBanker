//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#pragma once
#include "account.h"

using namespace std;

ostream &operator<<(ostream &os, const Account &acc) {
  os << acc.firstName << " " << acc.lastName << " ID: " << acc.accNum << endl;

  for (int fundType = 0; fundType < 10; fundType++) {
    os << "\t" << FUNDS[fundType] << ": $" << acc.funds[fundType] << endl;
  }
  return os;
}

Account::Account(int accNum, string firstName, string lastName)
    : firstName(firstName), lastName(lastName) {
  if (accNum > 9999) {
    throw "err";
  } else {
    this->accNum = accNum;
  }
}

Account::~Account() { history.clear(); };

bool Account::withdraw(int fundType, int amt) {
  int totalMoneyMarket = funds[0] + funds[1];
  switch (fundType) {
  case 0:
    if (amt > funds[0]) {
      if (amt <= totalMoneyMarket) {
        funds[1] -= amt - funds[0];
        funds[0] = 0;
        history.push_back("\tW" + to_string(accNum) + to_string(amt));
        return true;
      } else {
          history.push_back("\tW" + to_string(accNum) + to_string(amt) + " (Failed)");
          return false;
      }
    }
    funds[0] -= amt;
    return true;
  case 1:
    if (amt > funds[1]) {
      if (amt <= totalMoneyMarket) {
        funds[0] -= amt - funds[1];
        funds[1] = 0;
        history.push_back("\tW " + to_string(accNum) + to_string(amt));
        return true;
      } else {
          history.push_back("\tW " + to_string(accNum) + to_string(amt) + " (Failed)");
          return false;
      }
    }
    funds[1] -= amt;
    return true;
  default:
    if (amt > funds[fundType]) {
        history.push_back("\tW " + to_string(accNum) + to_string(amt) + " (Failed)");
        return false;
    }
    funds[fundType] -= amt;
    history.push_back("\tW " + to_string(accNum) + to_string(amt));
    return true;
  }
}

bool Account::deposit(int fundType, int amt) {
  // invalid fund type
  if (!(fundType >= 0 && fundType <= 9))
    return false;
  if (amt > 0) {
    funds[fundType] += amt;
    history.push_back("\tD " + to_string(accNum) + to_string(amt));
    return true;
  }
  history.push_back("\tD " + to_string(accNum) + to_string(amt) + " (Failed)");
  return false;
}

bool Account::transfer(Account &otherAcc, int fundType1, int fundType2, int amt) {
  if (funds[fundType1] >= amt) {
    otherAcc.deposit(fundType2, amt);
    if (&otherAcc == &*this) {
      // History should only include the transfer if it's to itself
      history.pop_back();
    }
    funds[fundType1] -= amt;
    history.push_back("\tT " + to_string(accNum) + to_string(amt));
    return true;
  }
  history.push_back("\tERROR: Insufficient funds to transfer.");
  return false;
}

const deque<string> Account::getHistory(int fundType) {
  deque<string> tmp;
  if(fundType = -1) {
    while (!history.empty()) {
      tmp.push_back(history.front());
      cout << history.front() << endl;
      history.pop_front();
    }
    while (!tmp.empty()) {
      history.push_back(tmp.front());
      tmp.pop_front();
    }

    return history;
  }
}

int Account::getAccountNumber() const {
  return accNum;
}

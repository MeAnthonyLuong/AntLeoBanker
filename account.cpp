//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#include "account.h"

using namespace std;

// Outputs the first name, last name, account number, and total funds in each
// fund type.
ostream& operator<<(ostream& os, const Account& acc) {
    os << acc.firstName << " " << acc.lastName << " ID: " << acc.accNum << endl;

    for (int fundType = 0; fundType < 10; fundType++) {
        os << "\t" << acc.FUNDS[fundType] << ": $" << acc.funds[fundType]
           << endl;
    }
    return os;
}

// Account constructor that takes in a 4 digit account number, first name,
// and last name.
Account::Account(int accNum, string firstName, string lastName)
    : firstName(firstName), lastName(lastName) {
    // the account number is greater than four digits, we will not handle that.
    if (accNum > 9999) {
        throw "err";
    } else {
        this->accNum = accNum;
    }
}

// Destructor that runs the clear function to free up used memory.
Account::~Account() { history.clear(); };

// Return true if a withdrawal was successful, false other wise. Takes in the
// fund type you want to withdraw from and the amount.
bool Account::withdraw(int fundType, int amt) {
    // append the fundType to the account number to add to the history log.
    string accountWithFund = to_string(accNum) + to_string(fundType);

    // Special case here, the money markets can rely on each other.
    int totalMoneyMarket = funds[0] + funds[1];
    switch (fundType) {
    case 0:
        if (amt > funds[0]) {
            if (amt <= totalMoneyMarket) {
                funds[1] -= amt - funds[0];
                funds[0] = 0;
                // push to history the successful withdrawal.
                history.push_back("\tW" + accountWithFund + " " +
                                  to_string(amt));
                return true;
            } else {
                // push to history a failed withdrawal.
                history.push_back("\tW" + accountWithFund + " " +
                                  to_string(amt) + " (Failed)");
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
                // push to history the successful withdrawal.
                history.push_back("\tW " + accountWithFund + " " +
                                  to_string(amt));
                return true;
            } else {
                // push to history a failed withdrawal.
                history.push_back("\tW " + accountWithFund + " " +
                                  to_string(amt) + " (Failed)");
                return false;
            }
        }
        funds[1] -= amt;
        return true;
    default:
        // only withdraw if we have enough money.
        if (amt > funds[fundType]) {
            // push to history a failed withdrawal.
            history.push_back("\tW " + accountWithFund + " " + to_string(amt) +
                              " (Failed)");
            return false;
        }
        funds[fundType] -= amt;
        // push to history a successful withdrawal.
        history.push_back("\tW " + accountWithFund + " " + to_string(amt));
        return true;
    }
}

// Returns true if a deposit was successful, false other wise. Takes in the fund
// type that should be deposited into and the amount to be deposited.
bool Account::deposit(int fundType, int amt) {
    // append the fund type to the account number to add to the history log.
    string accountWithFund = to_string(accNum) + to_string(fundType);
    // Invalid fund type.
    if (!(fundType >= 0 && fundType <= 9)) {
        return false;
    }

    // we should only allow deposites greater than 0.
    if (amt > 0) {
        funds[fundType] += amt;
        // add to history a successful deposit.
        history.push_back("\tD " + accountWithFund + " " + to_string(amt));
        return true;
    }
    // add a failed deposit to the history.
    history.push_back("\tD " + accountWithFund + " " + to_string(amt) +
                      " (Failed)");
    return false;
}

// Returns true if a transfer is successful, false other wise. Transfers amt
// money between the fundType1 of this account and fundType2 of  the other
// account.
bool Account::transfer(Account* otherAcc, int fundType1, int fundType2,
                       int amt) {
    // if we're given a null account we should return false.
    if (otherAcc == nullptr) {
        // this isn't working
        // Add to history an error transfering.
        history.push_back("\tERROR: Target account does not exist.");
        return false;
    }

    // append fund types to account numbers to later add to history log.
    string account1WithFund = to_string(accNum) + to_string(fundType1);
    string account2WithFund =
        to_string(otherAcc->getAccountNumber()) + to_string(fundType2);

    // only transfer if we have enough money.
    if (funds[fundType1] >= amt) {
        // if we have enough money go ahead and deposit the money to the other
        // account.
        otherAcc->deposit(fundType2, amt);
        if (otherAcc == this) {
            // Because the transfered money to otherAcc should be logged as a
            // deposit we need to remove the deposit if we are transferring to
            // ourselves. If we transfer to ourselves, history should show a
            // transfer and not a deposit.
            history.pop_back();
        }
        // Take away the transferred amount.
        funds[fundType1] -= amt;
        // add to history a successful transfer.
        history.push_back("\tT " + account1WithFund + " " + to_string(amt) +
                          " " + account2WithFund);
        return true;
    }
    // Log to history a failed transfer due to Insufficient funds.
    history.push_back("\tERROR: Insufficient funds to transfer.");
    return false;
}

// Displays the history according to fundType. If no fund type is provided the
// function will display history logs for each fund type.
void Account::getHistory(int fundType) {
    for (auto it = history.begin(); it != history.end(); it++) {
        cout << *it << endl;
    }
}

// Returns the account number of this account.
int Account::getAccountNumber() const { return accNum; }

//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#include "account.h"

using namespace std;

// Outputs the first name, last name, account number, and total funds in each
// fund type.
ostream& operator<<(ostream& os, const Account& acc) {
    os << acc.firstName << " " << acc.lastName << " Account ID: " << acc.accNum
       << endl;

    for (int fundType = 0; fundType < 10; fundType++) {
        os << "\t" << acc.fundsName[fundType] << ": $" << acc.funds[fundType]
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
Account::~Account() = default;

// Return true if a withdrawal was successful, false other wise. Takes in the
// fund type you want to withdraw from and the amount.
bool Account::withdraw(int fundType, int amt) {
    // append the fundType to the account number to add to the history log.
    string accountWithFund = to_string(accNum) + to_string(fundType);
    // Special case here, the money markets can rely on each other.
    int totalMoneyMarket = funds[0] + funds[1];

    // special case for MoneyMarkets
    if (fundType == 0 && amt <= totalMoneyMarket && amt > funds[0]) {
        funds[1] -= amt - funds[0];
        funds[0] = 0;
        history[fundType].getHistory()->push_back("\tW " + accountWithFund +
                                                  " " + to_string(amt));
        return true;
    }

    // special case for MoneyMarkets
    if (fundType == 1 && amt <= totalMoneyMarket && amt > funds[1]) {
        funds[0] -= amt - funds[1];
        funds[1] = 0;
        history[fundType].getHistory()->push_back("\tW " + accountWithFund +
                                                  " " + to_string(amt));
        return true;
    }

    // default failed withdraw
    if (amt > funds[fundType]) {
        // push to history a failed withdrawal.
        history[fundType].getHistory()->push_back(
            "\tW " + accountWithFund + " " + to_string(amt) + " (Failed)");
        return false;
    }

    // default pass withdraw
    // only withdraw if we have enough money.
    if (funds[fundType] >= amt) {
        // push to history a successful withdrawal.
        history[fundType].getHistory()->push_back("\tW " + accountWithFund +
                                                  " " + to_string(amt));
        funds[fundType] -= amt;
        return true;
    }
    return false;
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
        history[fundType].getHistory()->push_back("\tD " + accountWithFund +
                                                  " " + to_string(amt));
        return true;
    }
    // add a failed deposit to the history.
    history[fundType].getHistory()->push_back("\tD " + accountWithFund + " " +
                                              to_string(amt) + " (Failed)");
    return false;
}

// Returns true if a transfer is successful, false other wise. Transfers amt
// money between the fundType1 of this account and fundType2 of  the other
// account.
bool Account::transfer(Account* otherAcc, int fundType1, int fundType2,
                       int amt) {
    // append fund types to account numbers to later add to history log.
    string account1WithFund = to_string(accNum) + to_string(fundType1);
    string account2WithFund =
        to_string(otherAcc->getAccountNumber()) + to_string(fundType2);

    // only transfer if we have enough money.
    if (funds[fundType1] >= amt) {
        // if we have enough money go ahead and deposit the money to the other
        // account.
        otherAcc->deposit(fundType2, amt);
        if (otherAcc == this && fundType1 == fundType2) {
            // Because the transfered money to otherAcc should be logged as a
            // deposit we need to remove the deposit if we are transferring to
            // ourselves. If we transfer to ourselves, history should show a
            // transfer and not a deposit.
            history[fundType1].getHistory()->pop_back();
        }
        // Take away the transferred amount.
        funds[fundType1] -= amt;
        // add to history a successful transfer.
        history[fundType1].getHistory()->push_back("\tT " + account1WithFund +
                                                   " " + to_string(amt) + " " +
                                                   account2WithFund);
        return true;
    }
    // Log to history a failed transfer due to Insufficient funds.
    history[fundType1].getHistory()->push_back(
        "\tERROR: Insufficient funds to transfer.");
    return false;
}

// Displays the history according to fundType. If no fund type is provided the
// function will display history logs for each fund type.
void Account::getHistory(int fundType) {
    // [MoneyMarket, OtherFunds, n]
    string accountName = firstName + " " + lastName;
    if (fundType == -1) {
        cout << "Displaying Transaction History for " << accountName
             << " by fund." << endl;
        for (int i = 0; i < MAX_ACC; i++) {
            cout << fundNames[i] << ": $" << funds[i] << endl;
            if (history[i].getHistory()->empty()) {
                cout << history[i];
            } else {
                cout << history[i] << endl;
            }
        }
    } else {
        cout << "Displaying Transaction History for " << accountName << "'s "
             << fundNames[fundType] << ": $" << funds[fundType] << endl;
        cout << history[fundType] << endl;
    }
}

// Returns the account number of this account.
int Account::getAccountNumber() const { return accNum; }

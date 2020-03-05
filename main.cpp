#include "account.h"
#include "accounttree.h"
#include "bank.h"

#include <sstream>

int main() {
    Account* acc1 = new Account(1234, "John", "Doe");
    Account* acc2 = new Account(1235, "Jayn", "pope");
    Account* acc3 = new Account(1233, "Jhhn", "gdr");
    acc1->deposit(1, 60);
    acc1->deposit(0, 600);
    acc1->deposit(6, 70);
    acc1->deposit(9, 90);
    acc1->deposit(3, 30);
    cout << acc1 << endl;
    acc1->withdraw(0, 660);
    cout << acc1 << endl;
    acc1->transfer(*acc1, 9, 90);
    cout << acc1 << endl;
    acc1->getHistory();

    AccountTree* tree = new AccountTree();
    tree->insert(acc1);
    cout << (tree->insert(acc2) == 0 ? "false" : "true");
    cout << (tree->insert(acc3) == 0 ? "false" : "true");
    tree->display();
    cout << (tree->isEmpty() == 0 ? "false" : "true");
    delete tree;

    string line = "O Cash Johny 1234";
    string arr[6];
    int i = 0;
    stringstream ssin(line);
    while (ssin.good() && i < 6) {
        ssin >> arr[i];
        ++i;
    }
    for (i = 0; i < 4; i++) {
        cout << arr[i] << endl;
    }

    cout << stoi("fdsfsfs");

    Bank bank("input.txt");
    bank.displayAllBankBalances();
}

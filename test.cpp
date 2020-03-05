#include "account.h"
#include "accounttree.h"

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
    cout << (tree->insert(acc2) == 0 ? "false" : "true");
    cout << (tree->insert(acc2) == 0 ? "false" : "true");
    cout << (tree->insert(acc3) == 0 ? "false" : "true");
    tree->display();
    cout << (tree->isEmpty() == 0 ? "false" : "true");
    cout << "uh" << endl;
}
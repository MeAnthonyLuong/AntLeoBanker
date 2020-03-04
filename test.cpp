#include "account.h"

int main() {
    Account acc1(1234, "John", "Doe");
    acc1.deposit(1, 60);
    acc1.deposit(0, 600);
    acc1.deposit(6, 70);
    acc1.deposit(9, 90);
    acc1.deposit(3, 30);
    acc1.withdraw(0, 660);
    cout << acc1 << endl;
}
//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#pragma once
#include <queue>
using namespace std;

class Account {
  
  friend ostream& operator<<(ostream& os, const Account& acc);
  public:
    bool withdraw(int fundType, int amt);
    bool deposit(int fundType, int amt);
    
    const queue<string> getHistory();

  private:
    queue<string> history;
    const static int MAX_ACC = 10;
    int accNum;

    int funds[MAX_ACC];
    string firstName;
    string lastName;
};

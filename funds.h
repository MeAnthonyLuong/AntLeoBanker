//
// Created by Leonardo Mota-Villaraldo and Anthony Luong on 03/06/2020
//

#include <deque>
#include <iostream>

using namespace std;

class Funds {
    friend ostream& operator<<(ostream& os, const Funds& funds) {
        for (auto it = funds.history->begin(); it != funds.history->end();
             it++) {
            if (it == funds.history->end() - 1) {
                os << *it;
            } else {
                os << *it << endl;
            }
        }
        return os;
    }

  private:
    deque<string>* history = new deque<string>;

  public:
    ~Funds() { delete history; }
    deque<string>* getHistory() { return history; }
};

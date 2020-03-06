#include <deque>
class Funds {
    friend ostream& operator<<(ostream& os, MoneyMarket& moneyMarket) {
        for (int i = history.begin(); it != history.end(); it++) {
            cout << *it << endl;
        }
    }

  private:
    std::deque<Funds> history;

  public:
    std::deque<Funds> getHistory() { return history; }
    void display() const;
};
#include <deque>
using namespace std;
class Funds {
    friend ostream& operator<<(ostream& os, Funds& funds) {
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
    deque<string>* getHistory() { return history; }
};


//
// Anthony Luong and Leo Mota-Villaraldo on 03/06/2020
//

#include "bank.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
bool stringsMatch(const string& str1, const string& str2) {
    int currLine = 1;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            cout << "Line " << currLine << ": "
                 << "Char: " << (i + 1) << " " << (to_string(str1[i]))
                 << " does not match " << (to_string(str2[i])) << endl;
            return false;
        }
        if (str1[i] == '\n') {
            currLine++;
        }
    }

    return true;
}

string getStringFile(const string& fileName) {
    ifstream inStream;
    inStream.open(fileName);
    string line;
    string textFile;
    if (!inStream) {
        cout << "ERROR: No File Found Matching :" << fileName;
        return "";
    }

    while (!inStream.eof()) {
        getline(inStream, line);
        // occurs when we've reached the end of the txt file
        if (line.empty() && inStream.eof()) {
            break;
        }
        textFile += line + "\n";
    }

    inStream.close();

    return textFile;
}
void test1() {
    Bank bank("BankTransIn.txt");
    string expected = getStringFile("expected1.txt");
    string actual;

    stringstream ss;
    ss << bank;
    actual = ss.str();
    assert(actual == expected);
}
void test2() {
    Bank bank("BankTransIn2.txt");
    string expected = getStringFile("expected2.txt");
    string actual;

    stringstream ss;
    ss << bank;
    actual = ss.str();
    cout << actual;
    assert(actual == expected);
}

int main(int argc, char* argv[]) {
    Bank bank;
    // Note that tests were done in BankTransIn.txt
    for (int i = 1; i < argc; i++) {
        cout << "The command line argument(s) was " << argv[i] << endl;
        string fileName = argv[i];
        bank.processTransactions(fileName);
        // bank.displayAllBankBalances();
    }

    cout << "Done" << endl;
    cout << "\nNow running tests" << endl;
    test1();
    test2();
    return 0;
}

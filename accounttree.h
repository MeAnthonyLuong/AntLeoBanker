//
// Anthony Luong and Leo Mota-Villaraldo on 03/03/2020
//

#pragma once

#include "account.h"
#include <iostream>

class AccountTree {
  public:
    // Create BST
    AccountTree();

    // Delete all nodes in BST
    ~AccountTree();

    // Insert new account
    bool insert(Account* account);

    // Retrieve account
    // returns true if successful AND *Account points to account
    bool retrieve(const int& accountNumber, Account*& account) const;

    // Display information on all accounts
    void display() const;

    // delete all information in AccountTree
    void clear();

    // check if tree is empty
    bool isEmpty() const;

  private:

    Account* recRetrieve(const int& accNum, Account*& acc);
    class Node {
      public:
        explicit Node(Account* account)
            : account{account}, right{nullptr}, left{nullptr} {}

      private:
        Account* account;
        Node* right;
        Node* left;
    };

    Node* root;
};

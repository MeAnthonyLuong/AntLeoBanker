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

    Account* getAccount(const int& accNum);

    // Display information on all accounts
    void display() const;

    // delete all information in AccountTree
    void clear();

    // check if tree is empty
    bool isEmpty() const;

  private:
    class Node {
      public:
        explicit Node(Account* account)
            : account(account), right(nullptr), left(nullptr) {}
        Account* getAccount() const;
        Node* getRight() const;
        void setRight(Node* newNode);
        Node* getLeft() const;
        void setLeft(Node* newNode);

      private:
        Account* account;
        Node* right;
        Node* left;
    };

    Node* root;

    void display(Node* curr) const;
    Account* getAccount(const int& accNum, Node* curr);

    void recursiveRemove(Node* current);
};

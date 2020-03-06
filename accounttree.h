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
    class Node {
      public:
        // Constructor for Node class.
        explicit Node(Account* account)
            : account(account), right(nullptr), left(nullptr) {}
        // Returns an account pointer to the account of this node.
        Account* getNodeAccount() const;
        // Returns the right node of this node.
        Node* getRight() const;
        // Sets the right node of this node to newNode.
        void setRight(Node* newNode);
        // Returns the left node if this node.
        Node* getLeft() const;
        // Sets the left node of this node to newNode.
        void setLeft(Node* newNode);

      private:
        Account* account;
        Node* right;
        Node* left;
    };

    Node* root;

    // Private overloaded display function.
    void display(Node* curr) const;

    // Private function that gets the account given an account number and
    // starting node.
    Account* getAccount(const int& accNum, Node* curr) const;

    // Recursively frees up memory used up the AccountTree.
    void recursiveRemove(Node* current);
};

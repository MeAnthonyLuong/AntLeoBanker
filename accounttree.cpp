//
// Created by <Name> on <Date>.
//

#include "accounttree.h"
#include <iostream>
// empty

AccountTree::AccountTree() { root = nullptr; }

// Delete all nodes in BST
AccountTree::~AccountTree() = default;

// Insert new account
bool AccountTree::insert(Account* acc) { return insert(root, acc); }

bool AccountTree::insert(Node* curr, Account* acc) {
    if (curr == nullptr) {
        Node* newNode = new Node(acc);
        curr = newNode;
        return true;
    }

    if (acc->accNum < curr->account->accNum) {
        return insert(curr->left, acc);
    } else {
        return insert(curr->right, acc);
    }
}

// Retrieve account
// returns true if successful AND *account points to account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    return true;
}

Account* AccountTree::getAccount(const int& accNum) {
    getAccount(accNum, root);
}

Account* AccountTree::getAccount(const int& accNum, Node* curr) {
    if(curr == nullptr) {
        return nullptr;
    }
    
    if (accNum == curr->account->accNum) {
        return curr->account;
    }

    if (accNum < curr->account->accNum) {
        return getAccount(accNum, curr->left);
    } else {
        return getAccount(accNum, curr->right);
    }

}

    // Display information on all accounts
    void AccountTree::display() const {
    display(root);
}

void AccountTree::display(Node* curr) const {
    if (curr == nullptr) {
        return;
    }
    display(curr->left);
    cout << "Not displaying fix" << endl;
    display(curr->right);
}

// delete all information in AccountTree
void AccountTree::clear() {}

// check if tree is empty
bool AccountTree::isEmpty() const { return true; }

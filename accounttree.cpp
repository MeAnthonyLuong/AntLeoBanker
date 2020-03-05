//
// Created by <Name> on <Date>.
//

#include "accounttree.h"
#include <iostream>
// empty

AccountTree::AccountTree() { root = nullptr; }

// Delete all nodes in BST
AccountTree::~AccountTree() { clear(); }

// Insert new account
bool AccountTree::insert(Account* acc) {
    if (this->root == nullptr) {
        this->root = new Node(acc);
        return true;
    }
    Node* curr = this->root;

    while (curr != nullptr) {
        if (acc->accNum > curr->getAccount()->accNum) {
            if (curr->getRight() == nullptr) {
                curr->setRight(new Node(acc));
                return true;
            }
            curr = curr->getRight();
        } else if (acc->accNum < curr->getAccount()->accNum) {
            if (curr->getLeft() == nullptr) {
                curr->setLeft(new Node(acc));
                return true;
            }
            curr = curr->getLeft();
        }
    }
    return false;
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
    if (curr == nullptr) {
        return nullptr;
    }

    if (accNum == curr->getAccount()->accNum) {
        return curr->getAccount();
    }

    if (accNum < curr->getAccount()->accNum) {
        return getAccount(accNum, curr->getLeft());
    } else {
        return getAccount(accNum, curr->getRight());
    }
}
AccountTree::Node* AccountTree::Node::getRight() const { return right; }

void AccountTree::Node::setRight(Node* newNode) { right = newNode; }

Account* AccountTree::Node::getAccount() const { return account; }

AccountTree::Node* AccountTree::Node::getLeft() const { return left; }

void AccountTree::Node::setLeft(Node* newNode) { left = newNode; }

// Display information on all accounts
void AccountTree::display() const { display(root); }

void AccountTree::display(Node* curr) const {
    if (curr == nullptr) {
        return;
    }
    display(curr->getLeft());
    cout << *(curr->getAccount()) << endl;
    display(curr->getLeft());
}

// delete all information in AccountTree
void AccountTree::clear() {
    if (isEmpty()) {
        cout << "There are no Accounts to delete" << endl;
        return;
    }
    recursiveRemove(root);
}

// check if tree is empty
bool AccountTree::isEmpty() const { return root == nullptr; }

void AccountTree::recursiveRemove(Node* curr) {
    if (curr == nullptr) {
        return;
    }
    recursiveRemove(curr->getLeft());
    recursiveRemove(curr->getRight());
    Account* tmp = curr->getAccount();
    delete tmp;
    delete curr;
}

//
// Created by <Name> on <Date>.
//

#include "accounttree.h"
#include <iostream>

// Default constructor.
AccountTree::AccountTree() { root = nullptr; }

// Delete all nodes in BST by calling clear.
AccountTree::~AccountTree() { clear(); }

// Inserts a new account into the AccountTree.
bool AccountTree::insert(Account* acc) {
    if (this->root == nullptr) {
        // if our root is null, then just set root equal to this acc.
        this->root = new Node(acc);
        return true;
    }
    // Set a current node to traverse through the binary tree.
    Node* curr = this->root;

    while (curr != nullptr) {
        // If the given accounts account number is greater than the current
        // account number then traverse to the right.
        if (acc->getAccountNumber() >
            curr->getNodeAccount()->getAccountNumber()) {
            // if the current node is null then we insert the account here.
            if (curr->getRight() == nullptr) {
                curr->setRight(new Node(acc));
                return true;
            }
            curr = curr->getRight();
            // If the given accounts account number is less than the current
            // account number then traverse to the left.
        } else if (acc->getAccountNumber() <
                   curr->getNodeAccount()->getAccountNumber()) {
            // if the current node is null then we insert the account here.
            if (curr->getLeft() == nullptr) {
                curr->setLeft(new Node(acc));
                return true;
            }
            curr = curr->getLeft();
        }
    }
    return false;
}

// returns true if successful AND *account points to account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    account = getAccount(accountNumber, root);
    return account != nullptr;
}

// Given an account number and a node, traverse the tree until a matching
// account number is found. If found return a pointer to the account, other wise
// return nullptr.
Account* AccountTree::getAccount(const int& accNum, Node* curr) const {
    if (curr == nullptr) {
        return nullptr;
    }
    if (accNum == curr->getNodeAccount()->getAccountNumber()) {
        // Account number was found, returning the pointer to the account.
        return curr->getNodeAccount();
    }

    if (accNum < curr->getNodeAccount()->getAccountNumber()) {
        return getAccount(accNum, curr->getLeft());
    } else {
        return getAccount(accNum, curr->getRight());
    }
}

// Returns a node pointer to the right node.
AccountTree::Node* AccountTree::Node::getRight() const { return right; }

// Sets the right node equal to the newNode.
void AccountTree::Node::setRight(Node* newNode) { right = newNode; }

// Returns an account pointer to the account.
Account* AccountTree::Node::getNodeAccount() const { return account; }

// Returns a node pointer to the left node.
AccountTree::Node* AccountTree::Node::getLeft() const { return left; }

// Sets the left node equal to newNode.
void AccountTree::Node::setLeft(Node* newNode) { left = newNode; }

// Display information on all accounts
void AccountTree::display() const { display(root); }

// Overloaded private version of display that displays all information on all
// accounts inside of the account tree.
void AccountTree::display(Node* curr) const {
    if (curr == nullptr) {
        return;
    }
    display(curr->getLeft());
    cout << *curr->getNodeAccount() << endl;
    display(curr->getRight());
}

// Delete all used memory in AccountTree
void AccountTree::clear() {
    if (isEmpty()) {
        cout << "There are no Accounts to delete" << endl;
        return;
    }
    // Call the recursiveRemove function by passing in a starting node, the
    // root.
    recursiveRemove(root);
}

// check if tree is empty
bool AccountTree::isEmpty() const { return root == nullptr; }

// Recursively removes a node. Works in a DFS way by going to the depth most
// left node first, deleting it then going back to the right node of the
// previous node, deleting that one and working its way until it deletes the
// root node last.
void AccountTree::recursiveRemove(Node* curr) {
    // exit condition.
    if (curr == nullptr) {
        return;
    }
    recursiveRemove(curr->getLeft());
    recursiveRemove(curr->getRight());
    delete curr->getNodeAccount();
}

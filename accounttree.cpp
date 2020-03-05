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
bool AccountTree::insert(Account *acc) {
  if (this->root == nullptr) {
    this->root = new Node(acc);
    return true;
  }
  Node *curr = this->root;

  while (curr != nullptr) {
    if (acc->accNum > curr->account->accNum) {
      if (curr->right == nullptr) {
        curr->right = new Node(acc);
        return true;
      }
      curr = curr->right;
    } else if (acc->accNum < curr->account->accNum) {
      if (curr->left == nullptr) {
        curr->left = new Node(acc);
        return true;
      }
      curr = curr->left;
    }
  }
  return false;
}

// Retrieve account
// returns true if successful AND *account points to account
bool AccountTree::retrieve(const int &accountNumber, Account *&account) const {
  return true;
}

Account *AccountTree::getAccount(const int &accNum) {
  getAccount(accNum, root);
}

Account *AccountTree::getAccount(const int &accNum, Node *curr) {
  if (curr == nullptr) {
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
void AccountTree::display() const { display(root); }

void AccountTree::display(Node *curr) const {
  if (curr == nullptr) {
    return;
  }
  display(curr->left);
  cout << *(curr->account) << endl;
  display(curr->right);
}

// delete all information in AccountTree
void AccountTree::clear() {
  if (isEmpty()) {
    cout << "There are no Accounts to delete" << endl;
    return;
  }
  recursiveRemove(root);
  if (root->right == nullptr && root->left == nullptr) {
    delete root;
  }
}

// check if tree is empty
bool AccountTree::isEmpty() const { return root == nullptr; }

void AccountTree::recursiveRemove(Node *curr) {
  if (isEmpty()) {
    return;
  }
  recursiveRemove(curr->left);
  recursiveRemove(curr->right);
  delete curr->account;
  delete curr;
}

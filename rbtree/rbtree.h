// Philipp Moura Srivastava
// 05.02.2020
// Illumio Coding Challenge
// Filename: rbtree.h
// Description: This file describes the red black tree class
// in a header file

#ifndef _rbt_h
#define _rbt_h

#include <string>
#include "exceptions.h"
#include <algorithm>

using namespace std;

template <class T>

class RBT {
public:

  RBT();

  ~RBT();

  void insert(T* item);

  T* search(const T &item) const;

private:

  struct Node {
    Node* parent;
    Node* right;
    Node* left;
    bool isBlack;
    T value;
  };

  Node* root;
  void fixInsert(Node* item);
  void rotateRight(Node* item);
  void rotateLeft(Node* item);
  void transplant(Node* u, Node* v);
  void destroy(Node* item);

};

#include "rbtree.cc"

#endif

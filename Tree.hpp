//
// Created by Anderson Porto on 11/13/22.
//

#ifndef INC_2_AVL_TREE_TREE_HPP
#define INC_2_AVL_TREE_TREE_HPP

#include <cstddef>
#include <iostream>

class Tree {
 public:
  Tree();

  Tree(int key);

  Tree(const Tree &other);

  Tree &operator=(const Tree &other);

  ~Tree();

  void insert(int key);

  void remove(int key);

  void print();

  struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
  };


 private:
  void makeEmpty(Node *t);

  Node *insert(int x, Node *t);

  void updateHeight(Node *t);

  Node *singleRightRotate(Node *k2);

  Node *singleLeftRotate(Node *k2);

  Node *doubleLeftRotate(Node *k3);

  Node *doubleRightRotate(Node *k3);

  Node *findMin(Node *t);

  Node *findMax(Node *t);

  Node *remove(int x, Node *t);

  int height(Node *t);

  int getBalance(Node *t);

  void printTree(Node *t);



 private:
  Node *root;

};

#endif //INC_2_AVL_TREE_TREE_HPP

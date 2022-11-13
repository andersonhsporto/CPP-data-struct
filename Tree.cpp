#include "Tree.hpp"

Tree::Tree() {
  this->root = NULL;
}

Tree::Tree(int key) {
  this->root = new Node;
  this->root->key = key;
  this->root->left = NULL;
  this->root->right = NULL;
  this->root->height = 1;
}

Tree::Tree(const Tree &other) {
  *this = other;
}

Tree &Tree::operator=(const Tree &other) {
  if (this != &other) {
    this->root = other.root;
  }
  return *this;
}

Tree::~Tree() {
  makeEmpty(this->root);
}

void Tree::insert(int key) {
  this->root = insert(key, this->root);
}

void Tree::remove(int key) {
  this->root = remove(key, this->root);
}

void Tree::print() {
  printTree(this->root);
}

void Tree::makeEmpty(Node *t) {
  if (t) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
}

Tree::Node *Tree::insert(int x, Node *t) {
  if (t == NULL) {
    t = new Node;
    t->key = x;
    t->left = t->right = NULL;
    t->height = 1;
  } else if (x < t->key) {
    t->left = insert(x, t->left);
    if (height(t->left) - height(t->right) == 2) {
      if (x < t->left->key) {
        t = singleRightRotate(t);
      } else {
        t = doubleLeftRotate(t);
      }
    }
  } else if (x > t->key) {
    t->right = insert(x, t->right);
    if (height(t->right) - height(t->left) == 2) {
      if (x > t->right->key) {
        t = singleLeftRotate(t);
      } else {
        t = doubleRightRotate(t);
      }
    }
  }
  updateHeight(t);
  return t;
}

void Tree::updateHeight(Tree::Node *t) {
  t->height = std::max(height(t->left), height(t->right)) + 1;
}

Tree::Node *Tree::singleRightRotate(Node *k2) {
  Node *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  updateHeight(k2);
  updateHeight(k1);
  return k1;
}

Tree::Node *Tree::singleLeftRotate(Node *k2) {
  Node *k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  updateHeight(k2);
  updateHeight(k1);
  return k1;
}

Tree::Node *Tree::doubleLeftRotate(Node *k3) {
  k3->left = singleLeftRotate(k3->left);
  return singleRightRotate(k3);
}

Tree::Node *Tree::doubleRightRotate(Node *k3) {
  k3->right = singleRightRotate(k3->right);
  return singleLeftRotate(k3);
}

Tree::Node *Tree::findMin(Node *t) {
  if (t == NULL) {
    return NULL;
  } else if (t->left == NULL) {
    return t;
  } else {
    return findMin(t->left);
  }
}

Tree::Node *Tree::findMax(Node *t) {
  if (t == NULL) {
    return NULL;
  } else if (t->right == NULL) {
    return t;
  } else {
    return findMax(t->right);
  }
}

Tree::Node *Tree::remove(int x, Node *t) {
  Node *temp;

  if (t == NULL) {
    return NULL;
  } else if (x < t->key) {
    t->left = remove(x, t->left);
  } else if (x > t->key) {
    t->right = remove(x, t->right);
  } else if (t->left && t->right) {
    temp = findMin(t->right);
    t->key = temp->key;
    t->right = remove(t->key, t->right);
  } else {
    temp = t;
    if (t->left == NULL) {
      t = t->right;
    } else if (t->right == NULL) {
      t = t->left;
    }
    delete temp;
  }
  if (t == NULL) {
    return t;
  }
  updateHeight(t);
  if (height(t->left) - height(t->right) == 2) {
    if (height(t->left->left) - height(t->left->right) == 1) {
      return singleRightRotate(t);
    } else {
      return doubleLeftRotate(t);
    }
  } else if (height(t->right) - height(t->left) == 2) {
    if (height(t->right->right) - height(t->right->left) == 1) {
      return singleLeftRotate(t);
    } else {
      return doubleRightRotate(t);
    }
  }
  return t;
}

int Tree::height(Node *t) {
  return t == NULL ? -1 : t->height;
}

int Tree::getBalance(Node *t) {
  return t == NULL ? 0 : height(t->left) - height(t->right);
}

void Tree::printTree(Node *t) {
  if (t) {
    printTree(t->left);
    std::cout << t->key << " ";
    printTree(t->right);
  }
}


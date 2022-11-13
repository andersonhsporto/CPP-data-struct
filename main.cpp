#include "Tree.hpp"

int main() {
  Tree tree(42);

  tree.insert(4);
  tree.insert(2);
  tree.insert(3);
  tree.insert(1);

  tree.print();
  return 0;
}
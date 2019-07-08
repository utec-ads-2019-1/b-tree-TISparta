#ifndef NODE_H
#define NODE_H

#include <iostream>

#include <vector>
#include <cassert>

template <typename T>
class BTree;

template <typename T>
class Node {
  int number_keys = 0;
  int number_children = 2;
  std::vector <T> key;
  std::vector <Node <T>*> child;
  bool is_leaf;

  public:
  Node (int degree, bool is_leaf = true): is_leaf(is_leaf) {
    key.resize(2 * degree - 1);
    child.resize(2 * degree);
  }

  int getNumberOfChildren () const { 
    if (is_leaf) return 0;
    return number_children; 
  }

  int getNumberKeys () const { return number_keys; }

  void setNumberKeys (int new_number_keys) {
    assert(0 <= new_number_keys and new_number_keys <= key.size());
    number_keys = new_number_keys;
    number_children = number_keys + 1;
    if (number_children < 2) number_children = 2;
  }

  bool getIsLeaf () const { return is_leaf; }

  void setIsLeaf (bool new_is_leaf) { is_leaf = new_is_leaf; }

  T getKeyAtPosition (int index) const {
    if (index >= number_keys or index < 0) {
      std::cout << "Error getting " << index << ' ' << number_keys << std::endl;
    }
    assert(0 <= index and index < number_keys);
    return key[index];
  }

  void setKeyAtPosition (int index, T key_value) {
    assert(0 <= index and index < number_keys);
    key[index] = key_value;
  }

  Node <T>*& getChildAtPosition (int index) {
    assert(0 <= index and index < number_children);
    return child[index];
  }

  void setChildAtPosition (int index, Node <T>* child_value) {
    assert(0 <= index and index < number_children);
    child[index] = child_value;
  }

  friend class BTree <T>;
};

#endif

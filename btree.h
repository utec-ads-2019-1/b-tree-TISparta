#ifndef BTREE_H
#define BTREE_H

#include <iostream>

#include "node.h"

// https://cs.stackexchange.com/questions/6799/are-degree-and-order-the-same-thing-when-referring-to-a-b-tree
// Considering
// degree: lower bound of the number of nodes in the B tree
// order: uppder bound of the number of nodes in the B tree
//
// This implementation does not allow duplications and its based of CLRS's implementation
template <typename T>
class BTree {
  public:
    BTree (unsigned degree) : degree(degree), root(new Node <T> (degree)) {};

    ~BTree() {}

    bool find (T value) {
      return search(root, value).first != nullptr;
    }

    bool insert (T value) {
      if (find(value)) return false;
      insert(root, value);
      return true;
    }

    bool remove (int value) {
      if (not find(value)) return false;
      // TO DO
      return true;
    }

    // In-order traversal
    void print () {
      std::vector <T> printed;
      print(root, printed);
      for (T elem: printed) std::cout << elem << ' '; std::cout << std::endl;
    }

    void print (Node <T>* x, std::vector <T>& printed) const {
      if (x == nullptr) return;
      int index = 0;
      while (index < x -> getNumberKeys()) {
        if (not x -> getIsLeaf()) print(x -> getChildAtPosition(index), printed);
        printed.push_back(x -> getKeyAtPosition(index));
        index++;
      }
      if (not x -> getIsLeaf()) print(x -> getChildAtPosition(index), printed);
    }


  private:
    typedef Node <T> node;
    unsigned degree;
    node* root = nullptr;

    // Returns the node and the index of value in the B-tree or
    // null if it is not found
    std::pair <node*, int> search (node* x, T value) {
      if (x == nullptr) return {nullptr, -1};
      int index = 0;
      while (index < x -> getNumberKeys() and value > x -> getKeyAtPosition(index)) {
        index++;
      }
      if (index < x -> getNumberKeys() and value == x -> getKeyAtPosition(index)) {
        return {x, index};
      }
      if (x -> getIsLeaf()) {
        return {nullptr, -1};
      }
      return search(x -> getChildAtPosition(index), value);
    }

    void fillNodeZ (node*& y, node*& z) {
      z -> setIsLeaf(y -> getIsLeaf());
      z -> setNumberKeys(degree - 1);
      for (int j = 0; j < degree - 1; j++) {
        z -> setKeyAtPosition(j, y -> getKeyAtPosition(j + degree));
      }
      if (not z -> getIsLeaf()) {
        for (int j = 0; j < degree; j++) {
          z -> setChildAtPosition(j, y -> getChildAtPosition(j + degree));
        }
      }
    }

    void getUpElement (node*& x, int index, node*& y, node*& z) {
      x -> setNumberKeys(x -> getNumberKeys() + 1);
      for (int j = x -> getNumberOfChildren() - 1; j > index; j--) {
        x -> setChildAtPosition(j, x -> getChildAtPosition(j - 1));
      }
      x -> setChildAtPosition(index + 1, z);
      for (int j = x -> getNumberKeys() - 1; j > index; j--) {
        x -> setKeyAtPosition(j, x -> getKeyAtPosition(j - 1));
      }
      x -> setKeyAtPosition(index, y -> getKeyAtPosition(degree - 1));
      y -> setNumberKeys(degree - 1);
    }

    void splitChild (node*& x, int index, node*& y) {
      node* z = new node(degree);
      fillNodeZ(y, z);
      getUpElement(x, index, y, z);
    }

    void insertNonFull (node*& x, T value) {
      int index = x -> getNumberKeys() - 1;
      if (x -> getIsLeaf()) {
        x -> setNumberKeys(x -> getNumberKeys() + 1);
        while (index >= 0 and value < x -> getKeyAtPosition(index)) {
          x -> setKeyAtPosition(index + 1, x -> getKeyAtPosition(index));
          index--;
        }
        x -> setKeyAtPosition(index + 1, value);
        return;
      }
      while (index >= 0 and value < x -> getKeyAtPosition(index)) {
        index--;
      }
      index++;
      if (x -> getChildAtPosition(index) -> getNumberKeys() == 2 * degree - 1) {
        splitChild(x, index, x -> getChildAtPosition(index));
        if (value > x -> getKeyAtPosition(index)) {
          index++;
        }
      }
      insertNonFull(x -> getChildAtPosition(index), value);
    }

    void insert (node*& x, T value) {
      if (x -> getNumberKeys() == 2 * degree - 1) {
        node* s = new node(degree, false);
        s -> setChildAtPosition(0, x);
        splitChild(s, 0, x);
        root = s;
        insertNonFull(s, value);
        return;
      }
      insertNonFull(x, value);
    }

};

#endif

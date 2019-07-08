#include <iostream>
#include <vector>
#include <algorithm>

#include "mocker/mocker.h"
#include "btree.h"

const int DEGREE = 3;
const int N_ELEMS = 100;

void initArray (std::vector <int>& array) {
  for (int i = 0; i < int(array.size()); i++) {
    array[i] = Mocker::generateRandomNumber <int> ();
  }
  std::random_shuffle(begin(array), end(array));
}

void testInsert (const std::vector <int>& element) {
  BTree <int>* btree = new BTree <int> (DEGREE);
  for (int elem: element) {
    btree -> insert(elem);
  }
  for (int elem: element) {
    if (not btree -> find(elem)) {
      std::cerr << "Could not found " << elem << " in B-Tree" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  delete btree;
}

int main(int argc, char *argv[]) {
  std::vector <int> element(N_ELEMS);
  initArray(element);
  testInsert(element);
  std::cout << "All test passed" << std::endl;
  return EXIT_SUCCESS;
}

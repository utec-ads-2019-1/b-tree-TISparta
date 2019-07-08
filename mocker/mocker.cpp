#include "mocker.h"

int Mocker::generateRandomInt (int min_val, int max_val) {
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution <std::mt19937::result_type> distribution(min_val, max_val);
  return distribution(rng);
}

char Mocker::generateRandomChar () {
  std::mt19937 rng;
  rng.seed(std::random_device()());
  int increment = generateRandomInt() % 26;
  return 'a' + increment;
}

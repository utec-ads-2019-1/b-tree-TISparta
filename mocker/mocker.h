#ifndef MOCKER_H
#define MOCKER_H

#include <random>
#include <type_traits>

const int MIN_VAL = 0;
const int MAX_VAL = 100;

class Mocker {
  public:
    template <typename T>
    static T generateRandomNumber (int min_val = MIN_VAL, int max_val = MAX_VAL) {
      if (std::is_same <T, int>::value) return generateRandomInt(min_val, max_val);
      if (std::is_same <T, char>::value) return generateRandomChar();
    }

  private:
    static int generateRandomInt (int min_val = MIN_VAL, int max_val = MAX_VAL);
    static char generateRandomChar ();
};

#endif


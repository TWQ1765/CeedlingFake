#include "FakeMe.h"

void giveMeNumbers(char values[], int size) {
  int i;
  for(i = 0; i < size; i++)
    values[i] = getNumber() + 5;
}
      
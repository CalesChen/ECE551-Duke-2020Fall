#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int l = low, r = high;
  while (l < r) {
    int mid = (l + r) / 2;
    int val = f->invoke(mid);
    if (val == 0) {
      return mid;
    }
    else if (val > 0) {
      r = mid;
    }
    else if (val < 0) {
      l = mid + 1;
    }
  }
  if (l != low && r != high) {
    return l - 1;
  }
  // Ahuuu, a little wired in this return value, return the bound of the range.
  return (l == low) ? low : high - 1;
}

#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t max = 0;
  if (n == 0)
    return max;
  size_t cur = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      cur += 1;
    }
    else {
      if (cur > max) {
        max = cur;
      }
      cur = 1;
    }
  }
  if (cur > max)
    max = cur;
  return max;
}

#include <cstdio>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> test;
  //25743968
  int a[] = {2, 5, 7, 4, 3, 0, 1, -1, 9, 6, 8, 11};
  for (int i = 0; i < 12; i++) {
    test.add(a[i]);
  }
  for (int i = 0; i < 8; i++) {
    std::cout << test.contains(a[i]);
  }
  //  test.lookup(100);
  test.remove(2);
  test.remove(4);
  test.remove(5);
  test.remove(6);
  test.remove(8);
  test.remove(9);
  test.remove(1);
  test.remove(0);
  test.add(4);
  test.add(5);
  test.remove(3);
  std::cout << test.contains(5);
  std::cout << test.contains(11);
  BstSet<int> copyC(test);
  BstSet<int> copy;
  copy.add(1);
  copy.add(2);
  copy = test;

  return 0;
}

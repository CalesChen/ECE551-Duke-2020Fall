#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test(int * array, size_t n, size_t expect) {
  size_t ans = maxSeq(array, n);
  if (ans == expect) {
    printf("Expected %zd while get %zd \n", expect, ans);
    return;
  }
  else {
    printf("Expected %zd while get %zd \n", expect, ans);
    for (int i = 0; i < n; i++) {
      printf("%d", array[i]);
    }
    printf("\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int a1[] = {};
  test(a1, 0, 0);
  int a2[] = {1, 1, 2, 3, 5, 8};
  test(a2, 6, 5);
  int a3[] = {1, 2, 3, 3, 2, 1, 1, 2, 3, 4, 5};
  test(a3, 11, 5);
  int a4[] = {65533, 65534, 65535};
  test(a4, 3, 3);
  int a5[] = {6};
  test(a5, 1, 1);
  int a6[] = {-2147483648, 2147483647};
  test(a6, 2, 2);
  return EXIT_SUCCESS;
}

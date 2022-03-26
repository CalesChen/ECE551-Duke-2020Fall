#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned, unsigned);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("A bug in power(%d,%d),Expected %d", x, y, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  run_check(2, 0, 1);
  run_check(2, 10, 1024);
  run_check(65535, 1, 65535);
  run_check(0xFFFFFFFF, 1, 0xFFFFFFFF);
  run_check(9, 3, 729);
  run_check(6, 3, 216);
  run_check(6, 2, 36);
  return EXIT_SUCCESS;
}

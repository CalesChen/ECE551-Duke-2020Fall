#include <assert.h>
#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class linearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class posFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2; }
};
class negFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max = 0;
  if (high < low) {
    throw std::invalid_argument("The input is not valid.\n");
  }
  else if (high == low) {
    max = 1;
  }
  else if (high > low) {
    max = log(high - low) / log(2) + 1;
  }
  CountedIntFn tbCheck(max, f, mesg);
  int ans = binarySearchForZero(&tbCheck, low, high);
  if (ans != expected_ans) {
    // throw std::range_error("The answer is not right");
    std::cerr << "The answer of " << mesg << "is not right\n"
              << "Expected " << expected_ans << "while get " << ans << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main() {
  SinFunction sf;
  linearFunction lf;
  posFunction pf;
  negFunction nf;
  check(&sf, 0, 150000, 52359, "Sinfunction");
  check(&lf, -100, 1, 0, "Linearfunction");
  check(&lf, -1, 100, 0, "LinearFunction");
  check(&lf, -100, -1, -2, "negtive LinearFunction");
  check(&lf, 1, 100, 1, "Positive LinearFunction");
  check(&pf, -100, 100, -100, "Posfunction");
  check(&pf, -100, -1, -100, "Posfunction");
  check(&pf, 1, 100, 1, "Posfunction");
  check(&nf, -100, 100, 99, "Negfunction");
  check(&nf, -100, -1, -2, "NegFunction");
  check(&nf, 1, 100, 99, "NegFunction");
  return EXIT_SUCCESS;
}

#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f(fname);
  if (!f.is_open()) {
    throw std::invalid_argument("This is an invalid filename. \n");
  }
  char ch;
  // Initialize the array.
  uint64_t * res = new uint64_t[257]();
  while (f.get(ch)) {
    unsigned char temp = (unsigned char)ch;
    res[temp] += 1;
  }
  res[256] = 1;
  return res;
}

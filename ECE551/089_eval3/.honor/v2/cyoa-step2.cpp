#include "head.h"

int main(int argc, char ** argv){
  if(argc != 2){
    throw std::invalid_argument(" We need one single command line argument.\n");
  }
  Pages test(argv[1]);
  test.Check_func();
  test.play();
}

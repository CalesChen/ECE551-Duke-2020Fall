#include "head.h"

int main(int argc, char ** argv){
  if(argc != 2){
    throw std::invalid_argument("The input commend line is not suitable.\n");
  }
  Page pg(argv[1]);
  std::cout<<pg;
}

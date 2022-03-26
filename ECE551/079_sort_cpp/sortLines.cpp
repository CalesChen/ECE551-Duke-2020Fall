#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

using namespace std;

void string_sort(std::istream & f) {
  std::string cur;
  std::vector<std::string> strings;
  //int len = 0;
  while (getline(f, cur)) {
    strings.push_back(cur);
  }
  std::sort(strings.begin(), strings.end());
  std::vector<std::string>::iterator it = strings.begin();
  while (it != strings.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    string_sort(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream f(argv[i]);
      if (!f.is_open()) {
        std::cerr << "Failed to open the file.\n" << std::endl;
        exit(EXIT_FAILURE);
      }
      string_sort(f);
    }
  }
}

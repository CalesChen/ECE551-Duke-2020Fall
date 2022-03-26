#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int max(int * al, int len) {
  int max = 0, index = 0;
  for (int i = 0; i < len; i++) {
    if (al[i] >= max) {
      max = al[i];
      index = i;
    }
  }
  return index;
}

int breaker(FILE * f) {
  int len = 26;
  int al[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c) - 'a';
      al[c] += 1;
    }
  }
  return (max(al, len) + 22) % 26;  //ensure that the key is in the correct range.
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file %s \n");
    return EXIT_FAILURE;
  }
  int key = breaker(f);
  //misunderstanding about the range of key. key may be negtive after my algorithm, so I need to consider the mod.
  /*if (key < 0 || key >= 26) {
    return EXIT_FAILURE;
  }*/
  printf("%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

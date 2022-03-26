#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void sortString(FILE * input) {
  if (input == NULL) {
    fprintf(stderr, "the input is invalid");
    exit(EXIT_FAILURE);
  }
  char ** rows = NULL;
  //size_t i = readString(rows,input);
  char * cur = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&cur, &sz, input) >= 0) {
    rows = realloc(rows, (i + 1) * sizeof(*rows));
    rows[i] = cur;
    cur = NULL;
    i += 1;
  }
  free(cur);

  sortData(rows, i);

  for (size_t j = 0; j < i; j++) {
    fprintf(stdout, "%s", rows[j]);
    free(rows[j]);
  }
  //printString(rows,i);

  free(rows);
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    sortString(stdin);
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      sortString(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the %dth file", i);
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}

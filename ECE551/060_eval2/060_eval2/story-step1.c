#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "The story template is missing.\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  //variable to get the line.
  char * cur = NULL;
  size_t sz = 0;
  while (getline(&cur, &sz, f) != -1) {
    alter(&cur, NULL, NULL, 0);
    free(cur);
    cur = NULL;
    sz = 0;
  }
  free(cur);
  //close the file
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close the file. \n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

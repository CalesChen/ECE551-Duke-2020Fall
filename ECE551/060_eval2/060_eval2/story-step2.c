#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "The word file is missing.\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  //Variable to get the line.
  char * cur = NULL;
  size_t sz = 0;
  catarray_t * catarr = malloc(sizeof(*catarr));  //struct to record the category
  catarr->arr = NULL;
  catarr->n = 0;
  while (getline(&cur, &sz, f) != -1) {
    parse(&cur, catarr);
    free(cur);
    cur = NULL;
    sz = 0;
  }
  //print the struct
  printWords(catarr);
  free(cur);
  //free the catarr struct
  for (int i = 0; i < catarr->n; i++) {
    for (int j = 0; j < catarr->arr[i].n_words; j++) {
      free(catarr->arr[i].words[j]);
    }
    free(catarr->arr[i].words);
    free(catarr->arr[i].name);
  }
  free(catarr->arr);
  free(catarr);
  ///close the File,
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close the file. \n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

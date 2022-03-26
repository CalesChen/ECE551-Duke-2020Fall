#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc == 1) {
    fprintf(stderr, "Missing words files and story template file. \n");
    exit(EXIT_FAILURE);
  }
  if (argc == 2) {
    fprintf(stderr, "Missing story template file. \n");
    exit(EXIT_FAILURE);
  }
  FILE * f1 = fopen(argv[1], "r");
  char * cur = NULL;
  size_t sz = 0;
  catarray_t * catarr = malloc(sizeof(*catarr));
  catarr->arr = NULL;
  catarr->n = 0;
  while (getline(&cur, &sz, f1) != -1) {
    parse(&cur, catarr);
    free(cur);
    cur = NULL;
    sz = 0;
  }
  free(cur);

  category_t * record = malloc(sizeof(*record));  // track the used words
  record->n_words = 0;
  record->name = "RECORD";
  record->words = NULL;
  FILE * f2 = fopen(argv[2], "r");
  char * cur2 = NULL;
  size_t sz2 = 0;
  while (getline(&cur2, &sz2, f2) != -1) {
    alter(&cur2, catarr, record, 0);
    free(cur2);
    cur2 = NULL;
    sz = 0;
  }
  free(cur2);
  for (int i = 0; i < record->n_words; i++) {
    free(record->words[i]);
  }
  free(record->words);
  free(record);

  for (int i = 0; i < catarr->n; i++) {
    for (int j = 0; j < catarr->arr[i].n_words; j++) {
      free(catarr->arr[i].words[j]);
    }
    free(catarr->arr[i].words);
    free(catarr->arr[i].name);
  }
  free(catarr->arr);
  free(catarr);
  if (fclose(f1) != 0) {
    fprintf(stderr, "Can't close the file. \n");
    exit(EXIT_FAILURE);
  }
  if (fclose(f2) != 0) {
    fprintf(stderr, "Can't close the file. \n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

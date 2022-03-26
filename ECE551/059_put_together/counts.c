#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  if (ans == NULL) {
    fprintf(stderr, "Can't initialize the struct counts_t\n");
    exit(EXIT_FAILURE);
  }
  ans->array = NULL;
  ans->length = 0;
  ans->unknown_len = 0;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown_len += 1;
    return;
  }
  // if we have the corresponding name
  for (int i = 0; i < c->length; i++) {
    if (strcmp(name, c->array[i]->string) == 0) {
      c->array[i]->counts += 1;
      return;
    }
  }
  // if the name is a new one
  one_count_t * cur = malloc(sizeof(*cur));
  cur->string =
      name;  //this name is in the heap. can use strdup() if the name is not in the heap
  /*if(cur->string == NULL){ // this is the corresponding part of strdup()
    fprintf(stderr, "Memory is not enough");
    exit(EXIT_FAILURE);
    }*/
  cur->counts = 1;
  one_count_t ** temp = realloc(c->array, (c->length + 1) * sizeof(*c->array));
  if (!temp) {  //avoid memory leak
    fprintf(stderr, "The memory is not enough");
    exit(EXIT_FAILURE);
  }
  c->array = temp;
  c->array[c->length] = cur;
  c->length += 1;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    fprintf(outFile, "%s: %zd\n", c->array[i]->string, c->array[i]->counts);
  }
  if (c->unknown_len > 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->unknown_len);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}

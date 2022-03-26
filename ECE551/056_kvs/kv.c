#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "The fname is invalid\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * array = malloc(sizeof(*array));
  if (array == NULL) {
    fprintf(stderr, "Can't initialize the struct\n");
    exit(EXIT_FAILURE);
  }
  array->length = 0;
  size_t sz = 0;
  char * cur = NULL;
  array->arr = NULL;
  while (getline(&cur, &sz, f) >= 0) {
    if (cur == NULL) {
      fprintf(stderr, "Can't get the input");
      exit(EXIT_FAILURE);
    }
    array->arr = realloc(array->arr, (array->length + 1) * sizeof(*(array->arr)));
    if (array->arr == NULL) {
      free(array);
      fprintf(stderr, "Can't initialize the array\n");
      exit(EXIT_FAILURE);
    }
    kvpair_t * pair = malloc(sizeof(*pair));
    //get key
    char * p_eq = strchr(cur, '=');
    if (p_eq != NULL) {
      *p_eq = '\0';
    }
    pair->key = cur;
    p_eq += 1;
    char * p_end = strchr(p_eq, '\n');
    if (p_end != NULL) {
      *p_end = '\0';
    }
    pair->value = p_eq;
    array->arr[array->length] = pair;
    cur = NULL;
    array->length += 1;
  }
  //array->length = i;
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close the file");
    exit(EXIT_FAILURE);
  }
  free(cur);
  return array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->arr[i]->key);
    // free(pairs->arr[i]->value);
    free(pairs->arr[i]);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < (pairs->length); i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i]->key, pairs->arr[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    char * temp = pairs->arr[i]->key;
    if (strcmp(temp, key) == 0) {
      return pairs->arr[i]->value;
    }
  }
  return NULL;
}

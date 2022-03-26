#include "rand_story.h"

#include <ctype.h>
void parse(
    char ** str,
    catarray_t *
        catarr) {  //this function will parse the words.txt and add it to the category array.
  char * start = *str;              //start point of the string
  char * pos = strchr(start, ':');  //find the position of ':'
  if (pos == NULL) {                // check the input format
    fprintf(stderr, "Missing a ':' \n");
    exit(EXIT_FAILURE);
  }
  char * cat = strndup(start, (size_t)(pos - start));
  pos += 1;
  char * end = strchr(pos, '\n');  // alternate the \n to \0
  if (end != NULL) {
    *end = '\0';
  }
  // check if there exists the corresponding name.
  for (int i = 0; i < catarr->n; i++) {
    if (strcmp(cat, catarr->arr[i].name) == 0) {  //find the corresponding category
      catarr->arr[i].n_words += 1;
      catarr->arr[i].words =
          realloc(catarr->arr[i].words,
                  catarr->arr[i].n_words * (sizeof(*(catarr->arr[i].words))));
      catarr->arr[i].words[catarr->arr[i].n_words - 1] = strdup(pos);
      free(cat);
      return;
    }
  }
  // create the new category
  catarr->n += 1;
  catarr->arr = realloc(
      catarr->arr,
      catarr->n *
          (sizeof(
              *catarr->arr)));  // the following will initialize the struct with size of 1
  catarr->arr[catarr->n - 1].n_words = 1;
  catarr->arr[catarr->n - 1].name = strdup(cat);
  catarr->arr[catarr->n - 1].words = malloc(sizeof(*catarr->arr[catarr->n - 1].words));
  catarr->arr[catarr->n - 1].words[0] = strdup(pos);
  free(cat);
}
void alter(
    char ** str,
    catarray_t * catarr,
    category_t * record,
    int flag) {  // this function will alternate the blank, with the reuse functionality.
  char * pos = *str;  //start point
  char * temp = pos;  // begining of searching
  while (1) {
    char * temp1 = strchr(temp, '_');  // record the first '_'
    if (temp1 == NULL) {
      break;
    }
    else {
      char * temp2 = strchr(temp1 + 1, '_');  //record the second '_'
      if (temp2 == NULL) {
        fprintf(stderr, "Can't find the '_' in pair!\n ");
        exit(EXIT_FAILURE);
      }
      char * pre = strndup(temp, temp1 - temp);
      char * cat = strndup(temp1 + 1, (size_t)(temp2 - temp1 - 1));  // get the category
      int back = atoi(cat);  // get the valid number
      /* char * temp_c = cat;   // check if the cat is only containing digits
      while (*temp_c != '\0') {
        if (!isdigit(*temp_c)) {
          back = 0;
          break;
        }
        temp_c++;
      }*/
      const char * replace;
      if (back >= 1) {
        if (record->n_words < back) {
          fprintf(stderr, "The replace integer is invalid.\n");
          exit(EXIT_FAILURE);
        }
        replace = record->words[record->n_words - back];  // choose the word backwards
      }
      else if (back == 0) {
        replace =
            chooseWord(cat, catarr);  // using chooseWord to randomly choose the word.
      }

      printf("%s%s", pre, replace);
      temp = temp2 + 1;
      free(pre);
      // add the word to the record
      if (catarr != NULL && record != NULL) {
        record->words =
            realloc(record->words, (record->n_words + 1) * (sizeof(*record->words)));
        record->words[record->n_words] = strdup(replace);
        record->n_words += 1;
        if (flag == 1 && back < 1) {
          delete (cat, replace, catarr);
        }
      }
      free(cat);
    }
  }
  printf("%s", temp);
}

void delete (char * cat, const char * replace, catarray_t * catarr) {
  // the corresponding index of the cap. And I will delete the corresponding word.
  int i = 0;
  for (; i < catarr->n; i++) {
    if (strcmp(cat, catarr->arr[i].name) == 0) {
      break;
    }
  }
  int j = 0;  // the correponding index of the word to be deleted
  for (; j < catarr->arr[i].n_words; j++) {
    if (strcmp(replace, catarr->arr[i].words[j]) == 0) {
      break;
    }
  }
  char ** temp = malloc((catarr->arr[i].n_words - 1) * sizeof(*catarr->arr[i].words));
  int l = 0;  // control the index of temp;
  for (int k = 0; k < catarr->arr[i].n_words; k++) {
    if (k == j) {
      free(catarr->arr[i].words[j]);
      continue;
    }
    temp[l] = catarr->arr[i].words[k];
    l += 1;
  }
  free(catarr->arr[i].words);
  catarr->arr[i].words = temp;
  catarr->arr[i].n_words -= 1;
}

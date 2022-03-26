#include<stdio.h>
#include<stdlib.h>
#include "rand_story.h"

int main(int argc, char ** argv){
    if(argc < 2){
        fprintf(stderr, "The word file is missing.\n");
        exit(EXIT_FAILURE);
    }
    FILE * f = fopen(argv[1],"r");
    char * cur = NULL;
    size_t sz = 0;
    catarray_t * catarr = malloc(sizeof(*catarr));
    catarr->arr = NULL;
    catarr->n = 0;
    while(getline(&cur,&sz,f) != -1){
        char * str = strdup(cur);
        parse(&str, catarr);
        free(cur);
    }
    printWords(catarr);
    
    for(int i = 0; i < catarr->n;i++){
      for(int j = 0; j < catarr->arr[i].n_words;j++){
	free(catarr->arr[i].words[j]);
      }
      free(catarr->arr[i].words);
    }
    free(catarr->arr);
    return EXIT_SUCCESS;
}

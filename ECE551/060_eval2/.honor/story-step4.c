#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "rand_story.h"

int main(int argc, char ** argv){
    int ch;
    int flag = 0;
    /* check the option -n */
    while((ch = getopt(argc,argv,"n")) != -1){
        switch (ch)
        {
        case 'n':
            flag = 1;
            break;
        case '?':
            fprintf(stderr, "The option is invalid. \n");
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
    // check the number of argument.
    if(flag == 0){
        if(argc == 1){
            fprintf(stderr, "Missing words files and story template file. \n");
            exit(EXIT_FAILURE);
        }
        if(argc == 2){
            fprintf(stderr, "Missing story template file. \n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        if(argc == 2){
            fprintf(stderr, "Missing words files and story template file. \n");
            exit(EXIT_FAILURE);
        }
        if(argc == 3){
            fprintf(stderr, "Missing story template file. \n");
            exit(EXIT_FAILURE);
        }
    }
    
    /* create the category_array */
    FILE * f1 = fopen(argv[optind],"r");
    char * cur = NULL;
    size_t sz = 0;
    catarray_t * catarr = malloc(sizeof(*catarr));
    catarr->arr = NULL;
    catarr->n = 0;
    while(getline(&cur,&sz,f1) != -1){
        char * str = strdup(cur);
        parse(&str, catarr);
        free(cur);
    }

    /* Print the result */
    category_t * record = malloc(sizeof(*record)); // track the used words
    record->n_words = 0;
    record->name = "RECORD";
    record->words = NULL;
    FILE * f2 = fopen(argv[optind + 1],"r");
    char * cur2 = NULL;
    size_t sz2 = 0;
    if(flag == 0){
       while(getline(&cur2, &sz2, f2) != -1){
            alter2(&cur2, catarr, record);
            free(cur2);
        } 
    }
    else{
       while(getline(&cur2, &sz2, f2) != -1){
            alter3(&cur2, catarr, record);
            free(cur2);
        } 
    }
    freeCate(record);
    freeCatarr(catarr);
    
    return EXIT_SUCCESS;
}
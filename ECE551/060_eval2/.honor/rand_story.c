#include "rand_story.h"

void alter(char ** str){
    char * pos = *str;
    char * temp = pos;
    while(1){
        char * temp1 = strchr(temp,'_');
        if(temp1 == NULL){
            break;
        }
        else{
            *temp1 = '\0'; // record the postion of '_' to print the result.
            char * temp2 = strchr(temp1+1,'_');
            if(temp2 == NULL ){
                fprintf(stderr, "Can't find the '_' in pair!\n ");
                exit(EXIT_FAILURE);
            }
            *temp2 = '\0'; //next, we can duplicate the string between two '_'
            char * cat = strdup(temp+1);
            const char * replace = chooseWord(cat, NULL);
            printf("%s%s",temp,replace);
            temp = temp2+1;
            free(cat);
        }
    }
    printf("%s",temp);
}
void parse(char ** str, catarray_t * catarr){
    char * start = *str;
    char * pos = strchr(start,':');
    if(pos == NULL){
        fprintf(stderr, "Missing a ':' \n");
        exit(EXIT_FAILURE);
    }
    *pos = '\0';
    pos += 1;
    char * end = strchr(pos, '\n');
    if(end != NULL){
        *end = '\0';
    }
    for(int i = 0; i < catarr->n;i++){
        if(strcmp(start, catarr->arr[i].name) == 0){
            catarr->arr[i].n_words += 1;
            catarr->arr[i].words = realloc(catarr->arr[i].words, catarr->arr[i].n_words * (sizeof(*(catarr->arr[i].words))));
            catarr->arr[i].words[catarr->arr[i].n_words - 1] = pos;
            return ; 
        }
    }
    catarr->n += 1;
    catarr->arr = realloc(catarr->arr, catarr->n * (sizeof(*catarr->arr)));
    catarr->arr[catarr->n - 1].n_words = 1;
    catarr->arr[catarr->n - 1].name = start;
    catarr->arr[catarr->n - 1].words = malloc(sizeof(*catarr->arr[catarr->n - 1].words));
    catarr->arr[catarr->n - 1].words[0] = pos;
}

void alter2(char ** str,catarray_t * catarr, category_t * record){
    char * pos = *str;
    char * temp = pos;
    while(1){
        char * temp1 = strchr(temp,'_');
        if(temp1 == NULL){
            break;
        }
        else{
            *temp1 = '\0';
            char * temp2 = strchr(temp1+1,'_');
            if(temp2 == NULL ){
                fprintf(stderr, "Can't find the '_' in pair!\n ");
                exit(EXIT_FAILURE);
            }
            *temp2 = '\0'; //next, we can duplicate the string between two '_'
            char * cat = strdup(temp1+1);
            int back = atoi(cat);
            char * temp_c = cat;
            while(*temp_c != '\0'){
                if(!isdigit(*temp_c)){
                    back = 0;
                    break;
                }
                temp_c ++;
            }
            const char * replace;
            if(back >= 1){
                if(record->n_words < back){
                    fprintf(stderr, "The replace integer is invalid.\n");
                    exit(EXIT_FAILURE);
                }
                replace = record->words[record->n_words - back];  // choose the word backwards
            }
            else{
                replace = chooseWord(cat, catarr);  // using chooseWord to randomly choose the word.
            }

            printf("%s%s",temp,replace);
            temp = temp2+1;
            free(cat);

            // add the word to the record
	    record->words = realloc(record->words, (record->n_words+1) *(sizeof(*record->words)));
	    record->words[record->n_words] = strdup(replace);
	    record->n_words += 1;
        }
    }
    printf("%s",temp);
}
void freeCate(category_t * cat){
  for(int i = 0; i < cat->n_words;i++){
    free(cat->words[i]);
  }
  free(cat);
}

void freeCatarr(catarray_t * catarr){
  for(int i = 0;i < catarr->n;i++){
    freeCate(catarr->arr + i);
  }
  free(catarr);
}

void alter3(char ** str,catarray_t * catarr, category_t * record){
    char * pos = *str;
    char * temp = pos;
    while(1){
        char * temp1 = strchr(temp,'_');
        if(temp1 == NULL){
            break;
        }
        else{
            *temp1 = '\0';
            char * temp2 = strchr(temp1+1,'_');
            if(temp2 == NULL ){
                fprintf(stderr, "Can't find the '_' in pair!\n ");
                exit(EXIT_FAILURE);
            }
            *temp2 = '\0'; //next, we can duplicate the string between two '_'
            char * cat = strdup(temp1+1);
            int back = atoi(cat);
            const char * replace;
            if(back >= 1){
                if(record->n_words < back){
                    fprintf(stderr, "The replace integer is invalid.\n");
                    exit(EXIT_FAILURE);
                }
                replace = record->words[record->n_words - back];  // choose the word backwards
            }
            else{
                
                replace = chooseWord(cat, catarr);  // using chooseWord to randomly choose the word.
                delete(cat, replace, catarr);
            }

            printf("%s%s",temp,replace);
            temp = temp2+1;
            free(cat);

            // add the word to the record
	    record->words = realloc(record->words, (record->n_words+1) *(sizeof(*record->words)));
	    record->words[record->n_words] = strdup(replace);
	    record->n_words += 1;
        }
    }
    printf("%s",temp);
}
void delete(char * cat, const char * replace, catarray_t * catarr){
    int i = 0; // the corresponding index of the cap. And I will delete the corresponding word.
    for(; i < catarr->n;i++){
        if(strcmp(cat, catarr->arr[i].name) == 0){
            break;
        }
    }
    int j = 0;  // the correponding index of the word to be deleted
    for(; j < catarr->arr[i].n_words;j++){
        if(strcmp(replace,catarr->arr[i].words[j]) == 0){
            break;
        }
    }
    char ** temp = malloc((catarr->arr[i].n_words - 1) * sizeof(*catarr->arr[i].words));
    int l = 0; // control the index of temp;
    for(int k = 0; k < catarr->arr[i].n_words;i++){
        if(k == j){
            free(catarr->arr[i].words[j]);
            continue;
        }
        temp[l] = catarr->arr[i].words[k];
    }
    free(catarr->arr[i].words);
    catarr->arr[i].words = temp;
}
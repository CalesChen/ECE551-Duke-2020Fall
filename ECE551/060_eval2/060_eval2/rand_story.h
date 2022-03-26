#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
//this one will alternate the blank and print it .
void alter(char ** str, catarray_t * cararr, category_t * record, int flag);
//This one will help to delete the words in catarr->arr[i], so I can choose different words.
void delete_c(char * cat, const char * replace, catarray_t * catarr);
//This one will parese the line and get the catarr.
void parse(char ** str, catarray_t * catarr);
#endif

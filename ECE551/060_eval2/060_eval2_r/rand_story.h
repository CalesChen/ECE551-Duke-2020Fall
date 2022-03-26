#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//any functions you want your main to use
void alter(char ** str);
void alter2(char ** str,catarray_t * cararr, category_t * record);
void alter3(char ** str, catarray_t * cararr, category_t * record);
void delete(char * cat, const char * replace, catarray_t * catarr);
void parse(char ** str, catarray_t * catarr);
void freeCate(category_t * cat);
void freeCatarr(catarray_t * catarr);
#endif

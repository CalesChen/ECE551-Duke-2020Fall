#include<stdio.h>
#include<stdlib.h>
/*int main(){
    const char * const letters[2]= {"xr","ab"};
    //const char ** letter = (const char **) letters;
    printf("%c", letters[1][0]);
   getchar();
    
}*/
/*int f(int n, int *p, int ** q) {
int temp[2];
temp[0] = n + **q;
temp[1] = p[1];
*q = *q + 1;
printf("%d : %d : %d\n", n, temp[0], temp[1]);
if (n > 0) {
int x = f(n-1, temp, q);
*p = x + 2;
printf("%d / %d / %d\n", n, temp[1], x);
return temp[0] + x;
}
return 0;
}
int main(void) {
int a[] = {3,5,7,9,12,44};
int * p = a;
int b = f(2,a, &p);
printf("%d & %d & %d\n", a[0], a[1], b);
printf("%d & %d & %d\n", a[2], a[3], b);
getchar();
return EXIT_SUCCESS;*/
#include "pandemic.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  char *mark, *ch;
  size_t country_len;

  mark = line;
  ch = line;

  while (*ch != ',') {
    if (*ch == '\0') {
      fprintf(stderr, "Invalid input: don't have data");
      exit(EXIT_FAILURE);
    }
    ch++;
  }

  country_len = (size_t)(ch - mark);
  memcpy(ans.name, line, country_len);
  ans.name[country_len] = '\0';

  mark = ++ch;

  uint64_t tmp = 0ULL;
  while (*ch <= '9' && *ch >= '0') {
    tmp = tmp * 10ULL + (uint64_t)(*ch - '0');
    ch++;
  }

  if (ch == mark || (*ch != '\0' && *ch != '\n')) {
    fprintf(stderr, "Invalid input happens in data part\n");
    fprintf(stderr, "unexpected character \\x%02x at position %td. \n", *ch, ch - line);
    fprintf(stderr, "%s\n%*s\n", line, (int)(ch - line + 1), "^");
    exit(EXIT_FAILURE);
  }

  ans.population = tmp;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  int len = n_days - 6;
  for (int i = 0; i < len; i++) {
    double sum = 0;
    for (int j = i; j < i + 7; j++) {
      sum = sum + (double)data[j];
    }
    avg[i] = sum / 7.0;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  double sum = 0.0;
  for (size_t i = 0; i < n_days; i++) {
    sum += (double)data[i];
    cum[i] = sum / (double)pop * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_countries == 0 || n_days == 0)
    exit(EXIT_FAILURE);
  size_t max_country = 0;  // row represents the r_th country
  size_t max_case = 0;     // col represents the c_th days
  unsigned max = data[0][0];
  for (size_t r = 0; r < n_countries; r++) {
    for (size_t c = 0; c < n_days; c++) {
      if (data[r][c] > max) {
        max = data[r][c];
        max_country = r;
        max_case = c;
      }
    }
  }
  char * country_name = countries[max_country].name;
  unsigned number_cases = data[max_country][max_case];
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
}
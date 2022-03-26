#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

int getCountry_Name(char * line, country_t * ans) {
  int pos = 0;  //start position to get the country name
  while (line[pos] != ',') {
    ans->name[pos] = line[pos];  //as there is a \0 in ans.name[0];
    pos += 1;
    // Check the length of Country name;
    if (pos >= 64) {
      fprintf(stderr, "The Country name is too long to store\n");
      exit(EXIT_FAILURE);
    }
  }
  // printf("%s\n", line);
  // The Country Name should not be empty
  if (pos == 0) {
    fprintf(stderr, "The Country Name should not be empty\n");
    exit(EXIT_FAILURE);
  }
  /*if (line[pos] != ',') {
    fprintf(stderr, "The input of %s seems missing a ','\n", ans->name);
    exit(EXIT_FAILURE);
  }*/
  ans->name[pos] = '\0';
  pos += 1;
  // int start_population = pos;
  return pos;
}

void getCountry_Population(char * line, country_t * ans, int start_population) {
  int pos = start_population;   // this position is just after the ','
  int temp = atoi(line + pos);  // this is transition

  if (temp == 0) {  //chech the populaiton, the population should not be empty.
    fprintf(stderr, "%s population should not be empty\n", ans->name);
    exit(EXIT_FAILURE);
  }
  if (temp < 0) {
    fprintf(stderr, "%s population number is too large\n", ans->name);
    exit(EXIT_FAILURE);
  }
  ans->population = atoi(line + pos);
}

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  //ans.name[0] = '\0';
  ans.population = 0;

  //if line is Null Pointer
  if (!line) {
    fprintf(stderr, "The input seems to be invalid\n");
    exit(EXIT_FAILURE);
  }

  // the reason why I did not manipulate pointer is that I need to ensure the start pos.
  //int pos = 0; this line is invaild after abstraction

  //this will return the start position to get population
  int start_population = getCountry_Name(line, &ans);

  //Now we will get the population
  getCountry_Population(line, &ans, start_population);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (!data) {
    fprintf(stderr, "The data is invalid\n");
    exit(EXIT_FAILURE);
  }
  if (!avg) {
    fprintf(stderr, "I can not output!\n");
    exit(EXIT_FAILURE);
  }

  double sum = 0;  // this is the acumulation of the cases.
  for (int i = 0; i < n_days; i++) {
    sum += data[i];
    if (i >= 6) {
      avg[i - 6] = sum / 7;
      sum = sum - data[i - 6];
    }
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (!data) {
    fprintf(stderr, "The data is invalid\n");
    exit(EXIT_FAILURE);
  }
  if (!cum) {
    fprintf(stderr, "I can not output!\n");
    exit(EXIT_FAILURE);
  }
  double sum = 0;
  for (int i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = (sum / pop) *
             100000;  // for the calculation, we multiply 100000 outside the parenthesis.
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (!data) {
    fprintf(stderr, "Data is Invalid.\n");
  }
  if (!countries) {
    fprintf(stderr, "Countries struct is Invalid.\n");
  }
  int index_r =
      0;  // my algorithm is to scan the whole matrix, so this is for country_index
  unsigned max = 0;  // we can just return max as the max number.
  for (int i = 0; i < n_countries; i++) {
    for (int j = 0; j < n_days; j++) {
      unsigned cur = data[i][j];
      if (cur >= max) {
        max = cur;
        index_r = i;
      }
    }
  }
  char * country_name = countries[index_r].name;
  unsigned number_cases = max;
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}

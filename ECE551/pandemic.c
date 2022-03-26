#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

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
  int pos = 0;
  while (line[pos] != ',') {
    ans.name[pos] = line[pos];  //as there is a \0 in ans.name[0];
    pos += 1;
    // Check the length of Country name;
    if (pos >= 64) {
      fprintf(stderr, "The Country name is too long to store\n");
      exit(EXIT_FAILURE);
    }
  }

  // The Country Name should not be empty
  if (pos == 0) {
    fprintf(stderr, "The Country Name should not be empty\n");
    exit(EXIT_FAILURE);
  }

  ans.name[pos] = '\0';
  pos += 1;
  int start_population = pos;
  //Now we will get the population

  while (line[pos] >= '0' && line[pos] <= '9') {
    uint64_t temp = ans.population * 10 + (uint64_t)(line[pos] - '0');
    pos += 1;

    if (temp < ans.population) {
      fprintf(stderr, "The population number is wrong.\n");
      exit(EXIT_FAILURE);
    }
    ans.population = temp;
  }

  if (pos == start_population) {
    fprintf(stderr, "The population should not be empty\n");
    exit(EXIT_FAILURE);
  }

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

  double sum = 0;
  for (int i = 0; i < n_days; i++) {
    sum += data[i];
    //printf("%f\t", sum);
    if (i >= 6) {
      avg[i - 6] = sum / 7;
      sum = sum - data[i - 6];
    }
  }
  //avg[0] = sum / n_days;
}
double perCal(double cases, uint64_t pop, uint64_t per) {
  return (cases * per) / pop;
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
    cum[i] = perCal(sum, pop, 100000);
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
  int index_r = 0;  // index_c = 0;
  unsigned max = 0;
  for (int i = 0; i < n_countries; i++) {
    for (int j = 0; j < n_days; j++) {
      unsigned cur = data[i][j];
      if (cur >= max) {
        max = cur;
        index_r = i;
        // index_c = j;
      }
    }
  }
  char * country_name = countries[index_r].name;
  unsigned number_cases = max;
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}

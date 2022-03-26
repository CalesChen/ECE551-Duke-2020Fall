#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can't open the %s", filename);
    exit(EXIT_FAILURE);
  }

  counts_t * ans = createCounts();
  char * key = NULL;
  size_t sz = 0;
  ssize_t temp = 0;
  while ((temp = getline(&key, &sz, f)) != -1) {
    if (temp > 0 && key[temp - 1] == '\n') {
      key[temp - 1] = '\0';
    }
    addCount(
        ans,
        lookupValue(
            kvPairs,
            key));  // Attention: As the getline() will cover the original content, so don't need to free()
  }
  free(key);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close %s", filename);
    exit(EXIT_FAILURE);
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc == 1) {
    fprintf(stderr, "There is no Input\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair

    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Can't close the %s\n", outName);
      exit(EXIT_FAILURE);
    }

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}


#include <iostream>
using namespace std;

#include "RBitArray.h"

/**
 * Sort a disk file.
 */
int main(int argc, char* argv[]) {

  // We will output, at most, 10M integers.
  const int MaxOutputNumber = 10000000;

  RBitArray ba;
  if (!ba.allocate(MaxOutputNumber)) {
    cout << "Unable to allocate bit array" << endl;
    return EXIT_FAILURE;
  }
  ba.reset();

  // Read the input file which contains 1 integer per line. We read until the
  // end of the file, reading line by line. The data read at each line is
  // converted to an integer, and then the corresponding bit in the BitArray
  // is set to indicate that we ran across that number.

  FILE* input = fopen("xyz.dat", "r");
  char data[10];
  while (!feof(input)) {
    if (NULL != fgets(data, 10, input)) {
      ba.set(atoi(data));
    }
  }
  fclose(input);

  // Now, iterate over our entire BitArray. Whenever we come across a bit that
  // is set, we output the corresponding number.

  for (int i=0; i<MaxOutputNumber; i++) {
    if (ba.isSet(i)) {
      printf("%07d\n", i);
    }
  }

  // Return with good exit status
  return EXIT_SUCCESS;
}


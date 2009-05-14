
#include <iostream>
using namespace std;

#include "RBitArray.h"

/**
 * Output random numbers in the range 0 to 9999999.
 * A given number should not be output more than once.
 * The output should always be exactly 7 digits.
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

  // Initialize the random number generator.
  srand(getpid());

  // And generate numbers...
  
  for (int i=0; i<MaxOutputNumber; i++) {
    unsigned int num = (((double)rand())/RAND_MAX) * MaxOutputNumber;
    if (!ba.isSet(num)) {
      ba.set(num);
      printf("%07d\n", num);
    }
  }

  // Return with good exit status
  return EXIT_SUCCESS;
}


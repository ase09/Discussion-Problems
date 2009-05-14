#ifndef __RBITARRAY_H_
#define __RBITARRAY_H_

#include <stdlib.h>

typedef unsigned char	BYTE;		// consistent shortcut for a byte
const unsigned int	BBITS = 8; 	// number of bits in a byte

/**
 * The RBitArray class implements a Bit Field or Bit Array. The user may
 * allocate an array of the desired number of bits, and then use the methods
 * provided to get/set bits within the array.
 */
class RBitArray {

public:

  RBitArray();
  ~RBitArray();

  /**
   * @arraySize	The size of the bit field (number of bits)
   */
  bool allocate(unsigned long arraySize);

  /**
   * Get the size of the allocated array in BYTES.
   */
  unsigned long getSize();

  /**
   * Test whether the given bit is set.
   * @return	true if the given bit is set.
   */
  bool isSet(unsigned int number);

  /**
   * The following method should be used to manipulate the state of bits
   * within the array. The set/unset methods perform the action described
   * by the method name. The flip(...) method will change the state of
   * the bit.
   */

  void set(unsigned int number);
  void unset(unsigned int number);
  void flip(unsigned int number);

  /**
   * Invoking this method will reset all the bits in the array, i.e., every
   * bit will be set to false.
   */
  void reset();

  /**
   * Get the entire BYTE that contains the given bit within the array.
   */
  BYTE getByte(unsigned int number);

private:
  /**
   * Helper method. We need to first find the Byte and then the offset within
   * that Byte to get to the desired bit. This method gets the Byte index and
   * the bit offset for a given number.
   */
  void getIndexAndOffset(unsigned int number, size_t* index, size_t* offset);

private:
  unsigned long  size;	// size of the bit array
  BYTE*          array; // bit array
};

#endif // __RBITARRAY_H_


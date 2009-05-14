
#include <stdlib.h>
#include "RBitArray.h"

RBitArray::RBitArray() : size(0), array(NULL) {
}

RBitArray::~RBitArray() {
  if (NULL != array) {
    delete array;
    array = NULL;
  }
}

bool RBitArray::allocate(unsigned long arraySize) {
  // Validate that the requested size makes sense, i.e., positive.
  if (arraySize <= 0) {
    return false;
  }
  // If we have prior allocated the array, need to first free the
  // resources.
  if (NULL != array) {
    delete array;
  }
  // Our data structure is a BYTE array. The user specifies the requested
  // size in BITS. We need to divide the requested size by the number of bits
  // in a byte (BBITS) to get the desired size in BYTES.  
  // However, we also want to align the allocated array to a BYTE boundary.
  // An integer division will give us a BYTE aligned size, but may, due to 
  // rounding, return 1 less BYTE. Adding (BBITS-1) prior to the division 
  // ensures that we get the correct rounding (round up).
  size = (arraySize + (BBITS-1)) / BBITS;
  // We have the size, now go ahead and allocate the space. Return an error if
  // we are unable to allocate the memory.
  array = new BYTE[size];
  // If there was any error, re-initialize "size" also.
  if (NULL == array) {
    size = 0;
    return false;
  } else {
    return true;
  }
}

unsigned long RBitArray::getSize() {
  return size;
} 

/**  
 * Standard binary arithmetic and manipulations are used in the below methods
 * to set/unset the given bit.
 * The (1 << offset) construct gives us a bitmask with the appropriate bit set.
 * We then use this mask to set/unset and test the desired bit.
 */

/** 
 * Use the mask and the binary AND (&) operator to test the bit, e.g.,
 * Let's assume the 3rd and 6th bits in the 0 Byte are set (c = 01001000).
 * Test if bit #4 is set:
 *	mask = (1 << 4) = 00010000
 *	c & mask = 01001000 & 00010000 = 0
 * Test is bit #6 is set:
 *	mask = (1 << 6) = 01000000
 *	c & mask = 01001000 & 01000000 = 1
 */
bool RBitArray::isSet(unsigned int number) {
  size_t index, offset;
  getIndexAndOffset(number, &index, &offset);
  BYTE c = array[index];
  return (0 != (c & (1 << offset)));
}

/** 
 * To set a bit, we use the mask with the binary OR opertor (|), e.g.,
 * To set bit #3:
 *	mask = (1 << 3) = 00001000
 * 	c = ....[01]...
 *	c & mask = ....[01]... & 00001000 = ....1...
 */
void RBitArray::set(unsigned int number) {
  size_t index, offset;
  getIndexAndOffset(number, &index, &offset);
  array[index] |= (1 << offset);
}

/**
 * To unset a bit, we invert the mask. If we want to unset bit #3:
 *	mask = (1 << 3) = 00001000
 *	~mask = 11110111
 * 	c = ....[01]...
 *	c & ~mask = ....[01]... & 11110111 = ....0...
 */
void RBitArray::unset(unsigned int number) {
  size_t index, offset;
  getIndexAndOffset(number, &index, &offset);
  array[index] &= ~(1 << offset);
}

/**
 * To flip the bit, we use the XOR (^) operator. This results in the bit
 * flipping its value. If it was prior 0, to 1 and if it was prior 1, to 0.
 */
void RBitArray::flip(unsigned int number) {
  size_t index, offset;
  getIndexAndOffset(number, &index, &offset);
  array[index] ^= (1 << offset);
}

/**
 * Reset the entire array. We simply iterate over the entire range and invoke
 * the unset(...) method for each bit.
 */
void RBitArray::reset() {
  for (unsigned int i=0; i<size; i++) {
    unset(i);
  }
}

/**
 * Return the byte that contains the given bit.
 */
BYTE RBitArray::getByte(unsigned int number) {
  return array[number/8];
}

/**
 * Helper method that gets us the index into the byte and bit.
 * Integer division by 8 gets us the byte, e.g., The numbers 0-7 are
 * stored in the 0th bit, and (0..7)/8 all give 0, while (0..7)%8
 * results in 0..7 respectively.
 */
void RBitArray::getIndexAndOffset(unsigned int number, 
				size_t* index, size_t* offset) {
  *index = number / 8;
  *offset = number % 8;
}


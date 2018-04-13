/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: An implementation file to manage
 * bit-wise output to a file. Contains functions to flush
 * data to output byte by byte, writeBit to write
 * individual bits to a buffer
 */

#include "BitOutputStream.hpp"
#include <iostream>

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf);
    
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to 
 *  the bit buffer, and increment the bit buffer index.
 *  But flush the buffer first, if it is full. 
 */
void BitOutputStream::writeBit(int i) {
  // Is the bit buffer full? Then flush it.
  if (nbits == 8) {
    flush();
  }
    
  // Write the least significant bit of i into the buffer
  // at the current index
  buf = buf | (i << (7 - nbits));  
    
  // Increment the index
  nbits++;
}

/** Checks if buffer is empty.*/
bool BitOutputStream::isBufEmpty() {
  if (nbits == 0)
    return true;
  return false;
}

/** updates bitCount  */
void BitOutputStream::updateBitCount(int count) {
  bitCount += count;
}

/** returns bitCount  */
int BitOutputStream::getBitCount() {
  return bitCount;
};


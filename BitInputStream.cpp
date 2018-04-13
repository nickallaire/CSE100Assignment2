/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: An implementation file to manage bit-wise
 * input from a file. Contains functions to fill
 * buffer with a byte, readBit allows you to read
 * bit by bit
 */

#include "BitInputStream.hpp"
#include <iostream>
    
/** Fill the buffer from the input */
void BitInputStream::fill() {
  int nextByte;
  if ((nextByte = in.get()) == EOF)
    reachedEOF = true;
  buf = (unsigned char)nextByte;
  nbits = 0;
}

/** Read the next bit from the bit buffer.
 *  Fill the buffer from the input stream first if needed. 
 *  Return 1 if the bit read is 1;
 *  return 0 if the bit read is 0.
 *
 */
int BitInputStream::readBit() {
  int bit;
    
  // Have read all bits so break from decode
  if (bitCount == count)
    return bit = -1;
  count++;
    
  // If all bits in the buffer are read, fill the buffer first
  if (nbits == 8)
    fill();
    
  // Get the bit at the appriopriate location in the bit
  // buffer, and return the appropriate int
  bit = buf & (1 << (7 - nbits));
  if (bit != 0)
    for (int i = 0; i < (7-nbits); i++)
      bit /= 2;
    
  // Increment the index
  nbits++;
    
  return bit;
}

bool BitInputStream::getEOF() {
  return reachedEOF;   
}

void BitInputStream::setBitCount(int count) {
  bitCount = count;
};

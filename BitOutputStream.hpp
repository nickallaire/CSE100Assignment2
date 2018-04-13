/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: A header file to manage bit-wise
 * output to a file. Contains functions to flush
 * data to output byte by byte, writeBit to write
 * individual bits to a buffer
 */

#ifndef BitOutputStream_hpp
#define BitOutputStream_hpp

#include <stdio.h>

#include <iostream>

class BitOutputStream {
    
private:
  unsigned char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use
  int bitCount; //number of bits to encode;
    
public:
    
    
  /** Initialize a BitOutputStream that will use
   * the given ostream for output.
   */
  BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
    // clear buffer and bit counter
  }
    
  /** Send the buffer to the output, and clear it */
  void flush();
    
  /** Write the least significant bit of the argument to
   *  the bit buffer, and increment the bit buffer index.
   *  But flush the buffer first, if it is full.
   */
  void writeBit(int i);
  
  bool isBufEmpty();
    
  void updateBitCount(int count);
    
  int getBitCount();
};

#endif /* BitOutputStream_hpp */

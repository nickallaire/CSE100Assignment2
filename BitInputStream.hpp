/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: A header file to manage bit-wise
 * input from a file. Contains functions to fill 
 * buffer with a byte, readBit allows you to read 
 * bit by bit
 */

#ifndef BitInputStream_hpp
#define BitInputStream_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class BitInputStream {
    
private:
  unsigned char buf; // one byte buffer of bits
  int nbits; // how many bits have been read from buf
  std::istream & in; // the input stream to use
  bool reachedEOF = false;
  int bitCount;
  int count = 0;
    
public:
    
  /** Initialize a BitInputStream that will use
   * the given istream for input.
   */
  BitInputStream(std::istream & is) : in(is) {
      buf = 0;// clear buffer
      nbits = 0; // initialize bit index
  }
    
  /** Fill the buffer from the input */
  void fill();
    
  /** Read the next bit from the bit buffer.
   *  Fill the buffer from the input stream first if needed.
   *  Return 1 if the bit read is 1;
   *  return 0 if the bit read is 0.
   *
   */
  int readBit();
  
  /** Returns a boolean value
   *  True if reached EOF
   *  False if haven't reached EOF
   */
  bool getEOF();

  /** Sets bit count so you can keep
   *  track of how many bits you decoded
   */ 
  void setBitCount(int count);

};


#endif /* BitInputStream_hpp */

/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: A program that allows you
 * to compress a given input file, outputs
 * leaf count, frequency header, and encoded
 * data to output file
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    
  HCTree* hct = new HCTree();
  unsigned char nextChar;
  int nextByte;
  int bitCount;
  vector<int> freqs(256,0);
    
//Check for Arguments
  if(argc != 3){
    cout << "Invalid number of arguments.\n"
    << "Usage: ./compress <input filename> <output filename>.\n";
    return -1;
  }
    
  //Opens input  file
  ifstream in;
  in.open(argv[1], ios::binary);
  //in.open("pf/binary.dat");
  BitInputStream is(in);
    
  //Check if input file was actually opened
  if(!in.is_open()) {
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }
    
  //Check for empty file
  in.seekg(0, ios_base::end);
  unsigned long len = in.tellg();
  if(len==0) {
    cout << "The file is empty. \n";
    return -1;
  }
    
  //Resets the stream to beginning of file
  in.seekg(0, ios_base::beg);

  // Loads frequencies  
  while ((nextByte = in.get()) != EOF) {
    nextChar = (unsigned char) nextByte;
    freqs[nextByte] += 1;
  }
  
  nextByte = 0;
  in.close();
    
  hct->build(freqs);
    
  // Opens output file
  ofstream out;
  out.open(argv[2], ios::binary);
  //out.open("outputfile.txt");
  BitOutputStream os(out);
    
  // Gets leaf count in HCT
  int leavesCount = 0;
  for (int i = 0; i < freqs.size(); i++)
    if (freqs[i] != 0)
      leavesCount++;
  
  // Print leaf count at top of header
  out << leavesCount << "\n";
  //cout << leavesCount << "\n";   
 
  // Prints frequency to header in the format:
  // Frequency count
  // unsigned char value
  for (int i = 0; i < freqs.size(); i++) {
    if (freqs[i] != 0) {
      out << freqs[i] << "\n";
      out << i << "\n";
      leavesCount++;
    }      
  }

  in.open(argv[1], ios::binary);
  //in.open("pf/binary.dat");
  in.seekg(0, ios_base::beg);  
   
  // Encodes each byte 
  while ((nextByte = in.get()) != EOF) {
    nextChar = (unsigned char) nextByte;
    hct->encode(nextChar, os);
  }
  
  // If buf isn't empty after reaching
  // EOF, flush to get last couple bits
  if(!os.isBufEmpty())
    os.flush();
    
  bitCount = os.getBitCount();
  //cout << bitCount;
 
  // Stores bit count in new file 
  ofstream bitCountFile;
  bitCountFile.open("bitCountFile.txt", ios::binary);
  bitCountFile << bitCount;
    
    
  delete hct;
  in.close();
  out.close();
  bitCountFile.close();
    
}

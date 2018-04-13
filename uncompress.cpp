/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: A program that allows you
 * to uncompress a given input file, outputs
 * decoded bytes to create original encoded file
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
  int nextLoc;
  int nextFreq;
  int codedByte;
  string nextLine;
  int leaveCount;
  int bitCount;
  vector<int> freqs(256,0); // = new vector<int>(256, (int) 0);
    
  //Check for Arguments
  if(argc != 3){
    cout << "Invalid number of arguments.\n"
    << "Usage: ./compress <input filename> <output filename>.\n";
    return -1;
  }
    
  //Open input file
  ifstream in;
  in.open(argv[1], ios::binary);
  //in.open("outputfile.txt", ios::binary);

  // Open output file
  ofstream out;
  out.open(argv[2], ios::binary);
  //out.open("decodedMessae.txt", ios::binary);
    
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
    
  //Get bitCount from file
  ifstream bitCountFile;
  bitCountFile.open("bitCountFile.txt", ios::binary);
  bitCountFile >> bitCount;
   
  // Reads in frequencies from input 
  in >> leaveCount;
  for (int i = 0; i < leaveCount; i++) {
    in >> nextFreq;
    in >> nextLoc;
    freqs[nextLoc] = nextFreq;
  }

  // Empty file
  if (leaveCount == 0)
    return -1;
    
  // Repeat char whole file
  if (leaveCount == 1) {
    for (int i = 0; i < nextFreq; i++)
      out << (char) nextLoc;
      return -1;
  }
    
  hct->build(freqs);
    
  BitInputStream is(in);
  is.fill();
  is.fill();
  is.setBitCount(bitCount);

  // Decodes bytes, writes them to output file    
  while(1) {
    codedByte = hct->decode(is);
    if (codedByte == -1)
      break;
    out.put((unsigned char)codedByte);
  }
  
  delete hct;
  in.close();
  out.close();
  bitCountFile.close();   
}

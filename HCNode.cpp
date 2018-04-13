/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: An implementation file for Huffman Code Node
 */

#include <stdio.h>
#include "HCNode.hpp"

/** Compare this HCNode and other for priority
 ordering.
 * Smaller count means higher priority.
 * Use node symbol for deterministic tiebreaking
 */
bool HCNode::operator<(const HCNode& other) {
  // if counts are different, just compare counts
  if(count != other.count) return count > other.count;
  // counts are equal. use symbol value to break tie.
  // (for this to work, internal HCNodes
  // must have symb set.)
  return symbol < other.symbol;
}


//bool HCNode::comp(HCNode* one, HCNode* other) {
//    
//};

/* Nicholas Allaire
 * 4/22/16
 * Programming Assignment 2
 * Description: An implementation file for a Huffman Code Tree
 * Contains functions to build a tree, encode data, decode
 * data and delete all nodes from tree
 */

#include <stdio.h>
#include "HCTree.hpp"

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
HCTree::~HCTree() {
  deleteAll(root);
}

void HCTree::build(const vector<int>& freqs) {
  std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;

  // creates HCNodes, stores them in leaves vector, pushes onto queue    
  for (int i = 0; i < freqs.size(); i++) {
    if (freqs[i] != 0) {
      char symbol = (unsigned char) i;
      HCNode* temp = new HCNode(freqs[i], symbol, 0, 0, 0);
      leaves[i] = temp;
      pq.push(temp);
    }
  }
  
  while (pq.size() > 1) {
    HCNode* temp1;
    HCNode* temp2;
    temp1 = pq.top(); // gets smallest freq
    pq.pop();
    temp2 = pq.top(); // gets second smallest freq
    pq.pop();
    if (temp1->count < temp2->count) { // temp1 < temp2
      int count = temp1->count + temp2->count;
      HCNode* combNode = new HCNode(count, temp1->symbol, temp1, temp2, 0);
      temp1->p = combNode;
      temp2->p = combNode;
      if (pq.size() == 0) // queue is empty
        root = combNode;
        pq.push(combNode);
      } else if (temp2->count < temp1->count){ // temp2 < temp1
          int count = temp1->count + temp2->count;
          HCNode* combNode = new HCNode(count, temp2->symbol, temp2, temp1, 0);
          temp1->p = combNode;
          temp2->p = combNode;
          if (pq.size() == 0)
            root = combNode;
            pq.push(combNode);
      } else { // equal frequency
          if (temp1->symbol < temp2->symbol) { // compares symbol values
            int count = temp1->count + temp2->count;
            HCNode* combNode = new HCNode(count, temp1->symbol, temp1, temp2, 0);
            temp1->p = combNode;
            temp2->p = combNode;
            if (pq.size() == 0) // queue is empty
              root = combNode;
              pq.push(combNode);
          } else { // compares symbol values
              int count = temp1->count + temp2->count;
              HCNode* combNode = new HCNode(count, temp2->symbol, temp2, temp1, 0);
              temp1->p = combNode;
              temp2->p = combNode;
              if (pq.size() == 0) // queue is empty
                root = combNode;
            pq.push(combNode);
          }
      }      
  } 
}


/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
  long count = 0;
    
  int ascii = (int) symbol;
  HCNode* temp;
  vector<int> code;
  temp = leaves[ascii];

  while (temp-> p != nullptr) { // haven't reached root
    if (temp->p->c0 == temp)
      code.push_back(0);
    else
      code.push_back(1);
    temp = temp->p;
  }

  vector<int> tempCode;
  for (long i = code.size() - 1; i >= 0; i--) // reverses code
    tempCode.push_back(code[i]);

  code = tempCode;
  count = code.size();
  out.updateBitCount(count);
    
  for (long i = 0; i < code.size(); i++) // writes code to buffer
    out.writeBit(code[i]);
    
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const {
  HCNode* tempNode;
  tempNode = root;
  int bit;
    
  // haven't reached a leaf yet
  while (tempNode->c0 != nullptr && tempNode->c1 != nullptr) {
    bit = in.readBit();
    if (in.getEOF()) // reached EOF
      return -1;
        
    if (bit == 1)
      tempNode = tempNode->c1;
    else if (bit == 0)
      tempNode = tempNode->c0;
    else if (bit == -1) // read last bit from buffer
      return -1; //
  }
  return (int)tempNode->symbol;
}

void HCTree::deleteAll(HCNode* root) {
  if (root == nullptr)
    return;
  deleteAll(root->c0);
  deleteAll(root->c1);
  delete root;
};

/*
Nancy Hoang ndh9tsj
11/11/20
huffmanNode.h
*/

#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

#include <string>
using namespace std;

class huffmanNode {
 public:
  huffmanNode();
  ~huffmanNode();
  unsigned int frequency;
  unsigned char character;
  huffmanNode* left;
  huffmanNode* right;
  string path_taken; 
};

#endif

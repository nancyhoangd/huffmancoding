/*
Nancy Hoang ndh9tsj
11/11/20
heap.h
*/

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>
#include "huffmanNode.h"
using namespace std;

class heap {
 public:
  heap();
  ~heap();

  void insert(huffmanNode* node);
  huffmanNode* findMin();
  huffmanNode* deleteMin();
  unsigned int size();
  void makeEmpty();
  bool isEmpty();
  void print();

 private:
  vector<huffmanNode*> myHeap;
  unsigned int heap_size;

  void percolateUp(int hole);
  void percolateDown(int hole);
};

#endif



/*
Nancy Hoang ndh9tsj
11/11/20
heap.cpp
 */

#include "heap.h"
using namespace std;

// default constructor
heap::heap(){
  heap_size = 0;
  huffmanNode* temp = new huffmanNode;
  myHeap.push_back(temp);
}

//destructor
heap::~heap(){
}

void heap::insert(huffmanNode* node){
  myHeap.push_back(node);
  percolateUp(++heap_size);
}

void heap::percolateUp(int hole){
  huffmanNode* recentNode = myHeap[hole]; //recent inserted huffmannode pointer
  for ( ; (hole > 1) && (recentNode->frequency < myHeap[hole/2]->frequency) ; hole/=2){
    myHeap[hole] = myHeap[hole/2]; // move parent down 
  }
  myHeap[hole] = recentNode;
}

huffmanNode* heap::deleteMin(){
  if (heap_size == 0){
    throw "deleteMin() called on an empty heap";
  }
  huffmanNode* ret = myHeap[1];
  myHeap[1] = myHeap[heap_size--];
  myHeap.pop_back();
  if (!isEmpty()){
    percolateDown(1);
  }
  return ret;
}

void heap::percolateDown(int hole){
  huffmanNode* node = myHeap[hole];
  while (hole*2 <= heap_size){ // while there is a left child
    int child = hole*2; // left child
    //is there a right child? if so, it is lesser?
    if ((child+1 <= heap_size) && (myHeap[child+1]->frequency < myHeap[child]->frequency)){
      child++;
    }
    // if the child is greater than the node...
    if (node->frequency > myHeap[child]->frequency){
      myHeap[hole] = myHeap[child]; //move child up
      hole = child; // move hole down
    } else{
      break;
    }
  }
  myHeap[hole] = node; 
}

huffmanNode* heap::findMin(){
  if (heap_size == 0){
    throw "findMin() called on an empty heap";
  }
  return myHeap[1];
}

unsigned int heap::size(){
  return heap_size;
}

void heap::makeEmpty(){
  heap_size = 0;
  myHeap.resize(1);
}

bool heap::isEmpty(){
  return heap_size == 0;
}

void heap::print(){
  cout << "(" << myHeap[0]->frequency << ") ";
  for (int i = 1; i <= heap_size; i++){
    cout << myHeap[i]->frequency << " ";
    // next line is from http://tinyurl.com/mf9tbgm
    bool isPow2 = (((i+1) & ~(i)) == (i+1))? i+1 : 0;
    if (isPow2){
      cout << endl << "\t";
    }
  }
  cout << endl;
}

/*
Nancy Hoang ndh9tsj
11/11/20
huffmanNode.cpp
*/

#include "huffmanNode.h"
//using namespace std;

huffmanNode::huffmanNode(){
  frequency = 0;
  character = ' ';
  left = nullptr;
  right = nullptr;
  path_taken = "";
}

huffmanNode::~huffmanNode(){
}

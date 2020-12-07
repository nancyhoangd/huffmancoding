/*
Nancy Hoang ndh9tsj
11/11/20
huffmanenc.cpp
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "heap.h"
using namespace std;

vector<string> prefixCodes(256,"");
void determine_prefix_code(huffmanNode* node, string path){
  if (node->left != nullptr){ // if had children
    determine_prefix_code(node->right, path + "1");
    determine_prefix_code(node->left, path + "0");
  } else { // if no children
    prefixCodes[node->character] = path; 
  }
}

int main (int argc, char**argv){
  // FILE OPENING
  if (argc != 2){ // parameter check 
    cout << "Must enter the input file name and only itself!" << endl;
    exit(1);
  }
  ifstream file(argv[1]);
  if (!file.is_open()){ // attempt to open file
    cout << "Unable to open file" << endl;
    exit(2); 
  }
  
  // frequencies is a vector that contains the frequency of each char
  vector<int> frequencies(256,0); // each char's frequency count starts with 0

  // read the chars in file until end
  int totalSymbols = 0; 
  char character;
  while(file.get(character)){
    unsigned char c = character;
    if ((c < 0x20) || (c > 0x7e)){
      continue;
    }
    frequencies[c]++;
    totalSymbols++;
  }
  file.close();

  // CREATING THE BINARY HEAP CONTAINING HUFFMANNODE POINTERS 
  int distinctSymbols = 0;
  heap* binaryHeap = new heap();
  for (int i = 0; i < 256; i++){
    if (frequencies[i] != 0){
      distinctSymbols++;
      huffmanNode* node = new huffmanNode();
      node->frequency = frequencies[i];
      node->character = (char)(i);
      binaryHeap->insert(node);
    }
  }
  
  // BUILDING THE HUFFMAN TREE FROM THE BINARY HEAP
  while(binaryHeap->size() != 1){
    huffmanNode* node1 = binaryHeap->deleteMin();
    huffmanNode* node2 = binaryHeap->deleteMin();
    huffmanNode* parent = new huffmanNode();
    parent->frequency = (node1->frequency + node2->frequency);
    parent->left = node1;
    parent->right = node2;
    parent->character = '~';
    binaryHeap->insert(parent);
  }

  // DETERMINING THE PREFIX CODE OF EACH CHAR
  huffmanNode* huffmanTree = binaryHeap->findMin();
  string path_taken = "";
  for (int i = 0; i < 256; i++){
    if (frequencies[i] != 0){
      //string path_taken = "";
      determine_prefix_code(huffmanTree, path_taken);
    }
  }

  // FILE OUTPUT :o
  // reading in the file
  if (argc != 2){
    cout << "Must enter the input file name and only itself!" << endl;
    exit(1);
  }
  ifstream file2(argv[1]);
  if (!file2.is_open()){
    cout << "Unable to open file" << endl;
    exit(2); 
  }

  char character2;
  string encodedMessage = "";
  while(file2.get(character2)){
    encodedMessage += prefixCodes[character2] + " "; 
  }
  file.close();

  // print characters and their bit encodings
  for (int i = 0; i < 256; i++){
    if (frequencies[i] != 0){
      if ((char)(i) == ' '){
	cout << "space " <<  prefixCodes[i] << endl;	
      }else {
	cout << (char)(i) << " " <<  prefixCodes[i] << endl;
      }
    }
  }

  cout << "----------------------------------------" << endl;
  cout << encodedMessage << endl;
  cout << "----------------------------------------" << endl;
  cout << "There are a total of " << totalSymbols << " symbols that are encoded." << endl;
  cout << "There are " << distinctSymbols << " distinct symbols used." << endl;
  cout << "There are " <<  (8*totalSymbols) << " bits in the original file." << endl;

  int bitCount = 0; 
  for (int i = 0; i<encodedMessage.length(); i++){
    if (encodedMessage[i] != ' '){
      bitCount++;
    }
  }
  cout << "There are " << bitCount << " bits in the compressed file." << endl;
  float compressionRatio = (8*totalSymbols)/(float)bitCount;
  cout << "This gives a compression ratio of " << compressionRatio << "." << endl;

  //cost of huffman tree
  float huffmanCost = 0.0;
  float ratio = 0.0;
  int pathLength = 0;
  
  for (int i = 0 ; i < 256 ; i++){
    if (frequencies[i] > 0){
      ratio = (float)frequencies[i]/totalSymbols;
      pathLength = prefixCodes[i].length();
      huffmanCost += (ratio*pathLength);
    }
  }  
  cout << "The cost of the Huffman tree is " << huffmanCost << " bits per character." << endl; 
  
  return 0;
}


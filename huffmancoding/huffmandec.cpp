/*
Nancy Hoang ndh9tsj
11/11/20
huffmandec.cpp
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "huffmanNode.h"
using namespace std;

// RECURSIVE FUNCTION TO CREATE HUFFMAN TREE
void create_tree(huffmanNode* node, string prefix, char character){
  if (prefix.length() == 0){
    node->character = character; 
  } else{
    if (node->left == nullptr && node->right == nullptr){
      huffmanNode* node1 = new huffmanNode();
      huffmanNode* node2 = new huffmanNode();
      node->left = node1;
      node->right = node2;
    }
    if (prefix[0] == '0'){
      create_tree(node->left, prefix.substr(1), character);
    } else if (prefix[0] == '1'){
      create_tree(node->right, prefix.substr(1), character);
    }
  }
}

// main(): we want to use parameters
int main (int argc, char** argv) {
    // verify the correct number of parameters
    if (argc != 2) {
        cout << "Must supply the input file name as the only parameter" << endl;
        exit(1);
    }

    // attempt to open the supplied file
    // must be opened in binary mode as otherwise trailing whitespace is discarded
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }

    // VECTOR FOR HOLDING THE PREFIX CODES
    vector<string> prefixCodes(256, ""); 
    
    // read in the first section of the file: the prefix codes
    while (true) {
        string character, prefix;
        // read in the first token on the line
        file >> character;

        // did we hit the separator?
        if (character[0] == '-' && character.length() > 1) {
            break;
        }

        // check for space
        if (character == "space") {
            character = " ";
        }

        // read in the prefix code
        file >> prefix;
	      prefixCodes[character[0]] = prefix; 
    }

    // CREATING THE TREE
    huffmanNode* root = new huffmanNode();
    for (int i = 0; i < prefixCodes.size(); i++){
      if (prefixCodes[i] != ""){
	      create_tree(root, prefixCodes[i], (char) i); // segfaulting
      }
    }
    
    // read in the second section of the file: the encoded message
    stringstream sstm;
    while (true) {
        string bits;
        // read in the next set of 1's and 0's
        file >> bits;
        // check for the separator
        if (bits[0] == '-') {
            break;
        }
        // add it to the stringstream
        sstm << bits;
    }
    string allbits = sstm.str();
    file.close();

    // DECODING BELOW
    string message = "";
    huffmanNode* itr = new huffmanNode();
    itr = root;

    for (int i = 0; i < allbits.length(); i++){
      if (allbits[i] == '1'){
	      itr = itr->right;
	      if ((itr->left == nullptr) && (itr->right == nullptr)){ //@leaf
	        message+=itr->character;
	        itr = root; 
	      } 
      } else { //allbits[i] == '0'
	      itr = itr->left;
	      if ((itr->left == nullptr) && (itr->right == nullptr)){
	        message+=itr->character;
	        itr=root;
	      }
      }
    }
    cout << message << endl;
}

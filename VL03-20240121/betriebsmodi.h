#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void blackbox(vector<char> input, ofstream& k_text){
  for(const char &i : input){
    k_text << i;
  }
}

void ECB (const size_t t, ifstream& text, ofstream& k_text){ 
  const size_t block_size = t / 8; //da man mit char arbeitet und jeweils eins davon 8 Bit groß ist 
  int text_size;
  char byte = 0;

  vector <char > block; 
  size_t block_count = 0;

  while (text.get(byte))
  {
    if(block_count != block_size){
      block.push_back(byte);
      block_count++;
    }else{
      blackbox(block,k_text);
      block.clear();
      block_count = 1;
      block.push_back(byte);
    }
  }
  if(block_count != block_size){
    for(int i = block_count; i < block_size; i++){
      block.push_back('0');
    }
    blackbox(block,k_text);
  }
}

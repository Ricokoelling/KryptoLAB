#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

void blackbox(vector<bool> block, ofstream& output){
  bitset<8> out;
  size_t count = out.size()-1;
  for(const auto &i : block){
    if(count > 0){
      out[count] = i;
      count --;
    }else{
      out[count] = i;
      count= out.size()-1;    
      char text_out = out.to_ullong();
      output << text_out;
    }
  }
}

void char_to_bin (vector<char> block , vector<bool>& k){

    bitset<8> one_char;
    for(const char &c: block){
      one_char = c;
      for(int i = one_char.size() - 1; i >= 0; i--){
        k.push_back(one_char[i]);
      }
    }

    
}

void print_block(vector<bool> block){
  
  for(const auto &i : block){
    cout << i;
  }
  cout << endl;
}

void fill_zero(vector<bool>& block, size_t t){
  size_t size = block.size();
  cout << size << endl;
  while(size != t){
    block.push_back(0);
    size++;
  }
  print_block(block);
}

void ECB (size_t t, ifstream& input, ofstream& output){
  vector<bool> block(t);
  vector<char> char_block(t/8);
  block.clear();
  char_block.clear();
  char byte = 0;
  size_t count = 0;
  size_t max_char = t/8;
  while(input.get(byte))
  {
    if(count != max_char){
      char_block.push_back(byte);
      count++;
    }
    if(count == max_char){
      char_to_bin(char_block,block);
      blackbox(block, output);
      block.clear();
      char_block.clear();
      count=0;
    }
  }
  if(count != max_char){
    char_to_bin(char_block,block);
    fill_zero(block, t);
    blackbox(block, output);
  }
}

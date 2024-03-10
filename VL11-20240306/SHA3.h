#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>

using namespace std;


// Konstanten 
size_t D = 224; // Hashgroesse
size_t R = 1152; // Blockgroesse 
size_t C = 448; // Kapazität 
size_t B = C+R; //Blockbreite 1600  

string XOR(vector <string> input){

  size_t size = input[0].size();
  for(const auto &i : input){
    if(i.size() != size){
      cerr << "Wrong Sizes in XOR: " << size << " / " << i.size() << endl;
      return NULL; 
    }
  }
  string output(size, '0');
  int temp1, temp2;
  for(const auto &i : input){
    for(size_t j=0; j < size; j++){
      temp1 = output[j] - '0';
      temp2 = i[j] - '0';
      output += (((temp1 + temp2) % 2) + '0');
    }
  }
  return output;
}

char XOR(vector<char> input){
  char output = '0';
  for(const auto &i : input){
      output += ((((output-'0') + (i-'0')) % 2) + '0');
  }
  return output;
}

vector<string> pad(string input){
  size_t len = 0;
  vector<string> output;
  string inputPacked;
  for (int i = 0; i < input.length(); i++) {
    if (input[i] != ' ') {
        len++;
        inputPacked+= input[i];
    }
  }
  while(len - R >=0){
    output.push_back(inputPacked.substr(0, len-R));
    inputPacked.erase(0, len-R);
    len -= R;
  }
  if(len < R){
    for(size_t i = 0; i < len-R; i++){
      inputPacked+= '0';
    }
  }
  output.push_back(inputPacked);
  return output;
}

int getCoord( size_t i, size_t j, size_t k){
  return (i % 5) * 5 * 64 + (j % 5) * 64 + (k % 64);
}
char parityCol(string state, int j, int k){
  vector<char> output;
  output.push_back(state[getCoord(0,j,k)]);
  output.push_back(state[getCoord(1,j,k)]);
  output.push_back(state[getCoord(2,j,k)]);
  output.push_back(state[getCoord(3,j,k)]);
  output.push_back(state[getCoord(4,j,k)]);
  return XOR(output);
}
string theta (string state){
  string output;
  vector<char> xo;
  for(size_t i = 0; i < 5; i++){
    for(size_t j = 0; j < 5; j++){
      for(size_t k=0; k < 64; k++){
        xo.push_back(state[getCoord(i,j,k)]);
        xo.push_back(parityCol(state,j-1,k));
        xo.push_back(parityCol(state,j+1,k-1));
        output += XOR(xo);
      }
    }
  }
  return output;
}

string f(string state){
  for(size_t i = 0; i < 24;i++){
    state = theta(state);
  }
}

void sha3(string input){
  input.append("01");

  vector<string> blocks = pad(input);
  vector<string> xo;
  string state(B, '0');
  string k(C, '0');
  for(const auto &block: blocks){
    xo.push_back(state);
    xo.push_back(block+k);
    state = XOR(xo);
    state = f(state);
    xo.clear();
  }
  cout << state << endl;

}
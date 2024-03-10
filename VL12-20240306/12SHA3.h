#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>
#include <bitset>

using namespace std;


// Konstanten 
size_t D = 224; // Hashgroesse
int R = 1152; // Blockgroesse 
size_t C = 448; // Kapazität 
size_t B = C+R; //Blockbreite 1600  

vector<vector<int>> rotations =  {{0, 1, 62, 28, 27},
                                  {36, 44, 6, 55, 20},
                                  {3, 10, 43, 25, 39},
                                  {41, 45, 15, 21, 8},
                                  {18, 2, 61, 56, 14}};

vector<string> roundConstantsHex = {"0000000000000001",
    "0000000000008082",
    "800000000000808A",
    "8000000080008000",
    "000000000000808B",
    "0000000080000001",
    "8000000080008081",
    "8000000000008009",
    "000000000000008A",
    "0000000000000088",
    "0000000080008009",
    "000000008000000A",
    "000000008000808B",
    "800000000000008B",
    "8000000000008089",
    "8000000000008003",
    "8000000000008002",
    "8000000000000080",
    "000000000000800A",
    "800000008000000A",
    "8000000080008081",
    "8000000000008080",
    "0000000080000001",
    "8000000080008008"};

vector<string> roundConstants(){
  vector<string> output;
  stringstream ss;
  unsigned n;
  for(const auto &i : roundConstantsHex){
    ss << hex << i;
    ss >> n;
    bitset<64> b(n);
    output.push_back(b.to_string());
  }

  return output;
}

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
      output[j] = (((temp1 + temp2) % 2) + '0');
    }
  }
  return output;
}

char XOR(vector<char> input){
  char output = '0';
  for(const auto &i : input){
      output = ((((output-'0') + (i-'0')) % 2) + '0');
  }
  return output;
}

string AND(vector<string> input){
  size_t size = input[0].size();
  for(const auto &i : input){
    if(i.size() != size){
      cerr << "Wrong Sizes in AND: " << size << " / " << i.size() << endl;
      cout << input[0] << endl;
      cout << i << endl;
      return NULL; 
    }
  }
  string output = input[0];
  int temp1, temp2;
  for(const auto &i : input){
    for(size_t j=0; j < size; j++){
      temp1 = output[j] - '0';
      temp2 = i[j] - '0';
      if(temp1 == temp2 && temp1 == 1){
        output[j] = '1';
      }else{
        output[j] = '0';
      }
    }
  }
  return output;
}

string NOT(string input){
  string output;
  for(size_t i=0; i < input.size(); i++){
    if(input[i] == '1'){
      output += '0'; 
    }else{
      output += '1';
    }
  }
  return output;
}

vector<string> pad(string input){
  int len = input.size();
  vector<string> output;
  int blocksize = len - R;
  while(blocksize >=0){
    output.push_back(input.substr(0, blocksize));
    input.erase(0, blocksize);
    blocksize -= R;
  }
  if(blocksize < 0){
    for(int i = blocksize; i < 0; i++){
      input+= '0';
    }
  }else if(blocksize > 0){
    cerr << "Something went wrong!" << endl;
  }
  output.push_back(input);
  return output;
}

int getCoord( size_t i, size_t j, size_t k){
  int temp1 = (5 + (i % 5)) % 5;
  int temp2 = (5 + (j % 5)) % 5;
  int temp3 = ( 64+ (k %  64)) % 64;
  return temp1 * 5 * 64 + temp2 * 64 + temp3;
}

string getBlock(string state, size_t i, size_t j){
  return state.substr(getCoord(i,j,0), 64);
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
      for(size_t k= 0 ; k < 64; k++){
        xo.push_back(state[getCoord(i,j,k)]);
        xo.push_back(parityCol(state,j-1,k));
        xo.push_back(parityCol(state,j+1,k-1));
        if(XOR(xo) != '0' && XOR(xo) != '1'){
          cout << "WRONG " << i << " " << j << " " << k << endl;
          int test = XOR(xo);
          cout << "XOR: " << test << endl;
          cout << parityCol(state,j-1,k) << endl;
          cout << parityCol(state,j+1,k-1) << endl;
          exit(EXIT_FAILURE); 
        }
        output += XOR(xo);
      }
    }
  }
  return output;
}

string rho(string state){
  string output;
  for(size_t i=0; i< 5; i++){
    for(size_t j=0; j< 5; j++){
      output += getBlock(state,i,j).substr(64-rotations[i][j]);
      output += getBlock(state,i,j).substr(0,64-rotations[i][j]);
    }
  }
  return output;
}

string pi(string state){
  string output;
  for(size_t i=0; i< 5; i++){
    for(size_t j=0; j< 5; j++){
      output += getBlock(state,j,3*i+j);
    }
  }
  return output;
}

string chi(string state){
  string output;
  vector<string> send;
  vector<string> send2;
  for(size_t i=0; i< 5; i++){
    for(size_t j=0; j< 5; j++){
      send.push_back(getBlock(state,i,j));
      send2.push_back(NOT(getBlock(state,i,j+1)));
      send2.push_back(getBlock(state,i,j+2));
      send.push_back(AND(send2));
      output += XOR(send);
    }
  }
  return output;
}

string iota(string state, size_t i){
  vector<string> send;
  send.push_back(state.substr(0,64));
  send.push_back(roundConstants()[i]);
  return XOR(send)+state.substr(64);
}

string f(string state){
  for(size_t i = 0; i < 24;i++){
    state = theta(state);
    state = rho(state);
    state = pi(state);
    state = chi(state);
    state = iota(state,i);
  }

  return state;
}

string sha3(string input){
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
  return state.substr(0,D);
}

void exec(ifstream &input){
  string line, word,output;
  stringstream hexss;
  int n;
  while(getline(input, line, '\0')){
    stringstream ss(line);
    while(ss >> word){
      hexss << hex << word;
      hexss >> n;
      bitset<8> d(n);
      output += d.to_string();
      hexss.clear();
    }
  }
  cout << sha3(output) << endl;
}
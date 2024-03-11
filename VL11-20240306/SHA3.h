#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>

using namespace std;


// Konstanten 
int D = 224; // Hashgroesse
int R = 1152; // Blockgroesse 
int C = 448; // Kapazität 
int B = C+R; //Blockbreite 1600  

//converts hex to binary string
string Hex_to_bin(ifstream &input){
  string temp, output;
  while(input >> temp){
    for(size_t i= 0; i < temp.size(); i++){
      switch (temp[i])
      {
      case '0':
            output += "0000";
            break;
        case '1':
            output += "0001";
            break;
        case '2':
            output += "0010";
            break;
        case '3':
            output += "0011";
            break;
        case '4':
            output += "0100";
            break;
        case '5':
            output += "0101";
            break;
        case '6':
            output += "0110";
            break;
        case '7':
            output += "0111";
            break;
        case '8':
            output += "1000";
            break;
        case '9':
            output += "1001";
            break;
        case 'A':
        case 'a':
            output += "1010";
            break;
        case 'B':
        case 'b':
            output += "1011";
            break;
        case 'C':
        case 'c':
            output += "1100";
            break;
        case 'D':
        case 'd':
            output += "1101";
            break;
        case 'E':
        case 'e':
            output += "1110";
            break;
        case 'F':
        case 'f':
            output += "1111";
            break;

        default:
            cout << "\nInvalid hexadecimal digit " << endl;
            break;
      }
    }
  }
  return output;
}


//XOR multiple binary strings
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

//XOR bits
char XOR(vector<char> input){
  char output = '0';
  for(const auto &i : input){
      output = ((((output-'0') + (i-'0')) % 2) + '0');
  }
  if(output != '0' && output != '1'){
    cerr << "Something went wrong at Char XOR" << endl;
    cout << output << endl;
    for(const auto &i: input){
      cout << i << endl;
    }
    abort();
  }
  return output;
}

// padding for the input so it gets the needed length
vector<string> pad(string input){ // input binary
  input += "1";
  int len = input.size();
  vector<string> output;
  int temp = len - R;
  while(temp >=0){
    output.push_back(input.substr(0, len-R));
    input.erase(0, len-R);
    temp -= R;
  }
  if(len < R){
    for(size_t i = 0; i < abs(temp); i++){
      input+= '0';
    }
  }
  output.push_back(input);
  return output;
}

//calculates coordinates in strided array (string)
int getCoord( int i, int j, int k){
  int temp1 = (5 + (i % 5)) % 5;
  int temp2 = (5 + (j % 5)) % 5;
  int temp3 = ( 64+ (k %  64)) % 64;
  return temp1 * 5 * 64 + temp2 * 64 + temp3;
}

//calculates parity of a column
char parityCol(string state, int j, int k){
  vector<char> output;
  output.push_back(state[getCoord(0,j,k)]);
  output.push_back(state[getCoord(1,j,k)]);
  output.push_back(state[getCoord(2,j,k)]);
  output.push_back(state[getCoord(3,j,k)]);
  output.push_back(state[getCoord(4,j,k)]);
  return XOR(output);
}

// calculate parity of a column
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
        xo.clear();
      }
    }
  }
  return output;
}
//Permutation function
string f(string state){
  for(size_t i = 0; i < 24;i++){
    state = theta(state);
  }
  return state;
}

//SHA3
void sha3(ifstream &text, ofstream &output){
  string input = Hex_to_bin(text);
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
  output << state;

}
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>
#include <cmath>

using namespace std;
struct MaxKey
{
  string L1;
  string L2;
};

vector<string> Sbox{"e", "4", "d", "1", "2", "f", "b", "8", "3", "a", "6", "c", "5", "9", "0", "7"};
vector<string> invSbox{"e", "3", "4", "8", "1", "c", "a", "f", "7", "d", "9", "6", "b", "2", "0", "5"};
vector<int> Permutation{0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
vector<string> HEX = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};

vector<string> toBlock(ifstream &input){
  vector<string> output;
  string iss;
  while(input >> iss){
    output.push_back(iss);
  }

  return output;
}

bitset<4> hex_to_bitset(char hex){
  int temp = 0;
      if(hex - '0' > 9){
        temp = (hex - 'a') + 10;
      }else{
        temp = hex - '0';
      }

  return bitset<4>(temp);
}

int hex_to_int(string hex){
  int temp = 0;
      if(hex[0] - '0' > 9){
        temp = (hex[0] - 'a') + 10;
      }else{
        temp = hex[0] - '0';
      }
  return temp;
}

string XOR(string a, string b){

  stringstream  res;
  bitset<4> temp;
  string output, subs, subs2;
  temp = hex_to_bitset(a[0]) ^ hex_to_bitset(b[0]);
  res << hex << temp.to_ulong();
  return res.str();
}

string sbox(string input){
  if(input.size() != 1){
    return "0";
    cerr << "Wrong Hex size" << endl;
  }
  unsigned int temp;
  stringstream ss;
  string output;
  for(const char &i: input){
    ss << hex << i;
    ss >> temp;
    output.append(Sbox[temp]);
    ss=stringstream();
  }
  return output;
}

string invsbox(string input){
  if(input.size() != 1){
    return "0";
    cerr << "Wrong Hex size" << endl;
  }
  unsigned int temp;
  stringstream ss;
  string output;
  for(const char &i: input){
    ss << hex << i;
    ss >> temp;
    output.append(invSbox[temp]);
    ss=stringstream();
  }
  return output;
}

bool alpha(string x, string u2, string u4){
  vector<bitset<4>> xbin;
  for(size_t i=0; i < 4;i++){
    xbin.push_back(hex_to_bitset(x[i]));
  }
  bitset<4> u2bin = hex_to_bitset(u2[0]);
  bitset<4> u4bin = hex_to_bitset(u4[0]);

  if((xbin[1][3] ^ xbin[1][1] ^ xbin[1][0] ^ u2bin[3] ^ u2bin[1] ^ u4bin[3] ^ u4bin[1]) == 0){
    return true;
  }
  return false;
}

void init(ifstream &input, ifstream &crypttext){
  vector<string> block = toBlock(input);
  vector<string> cblock = toBlock(crypttext);
  MaxKey maxkey;
  int array[256] = {0};  //16^2

  string v2, v4, u2, u4;
  for(size_t i=0; i< block.size();i++){
    for(const auto &L1: HEX){
      for(const auto &L2: HEX){
        v2 = XOR(L1, cblock[i].substr(1,1));
        v4 = XOR(L2, cblock[i].substr(3,1));
        u2 = invsbox(v2);
        u4 = invsbox(v4);
        if(alpha(block[i],u2,u4)){
          array[hex_to_int(L1)+hex_to_int(L2)*16] += 1;
        }
      }
    } 
  }
  int max= -1, beta, second;
  for(const auto &L1: HEX){
      for(const auto &L2: HEX){
        second = block.size()/2;
        beta = abs(array[hex_to_int(L1)+hex_to_int(L2)*16]- second);
        if(beta > max){
          max = beta;
          maxkey.L1 = L1;
          maxkey.L2 = L2;
        }
      }
    } 

  cout << maxkey.L1 << " und " << maxkey.L2  << endl;
}
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>
#include <cmath>

using namespace std;

struct Approx{
  bitset<4> first;
  bitset<4> second;
};

vector<bitset<4>> U{bitset<4>("0000"), bitset<4>("0001"), bitset<4>("0010"), bitset<4>("0011"),
                    bitset<4>("0100"), bitset<4>("0101"), bitset<4>("0110"), bitset<4>("0111"),
                    bitset<4>("1000"), bitset<4>("1001"), bitset<4>("1010"), bitset<4>("1011"),
                    bitset<4>("1100"), bitset<4>("1101"), bitset<4>("1110"), bitset<4>("1111"),};

vector<bitset<4>> V;
vector<Approx> approx;

bitset<4> hexToBitset(char hex){
  int temp = 0;
  if(hex - '0' > 9){
      temp = (hex - 'a') + 10;
  }else{
    temp = hex - '0';
  }

  return bitset<4>(temp);
}

void setV(string sbox){
  for(size_t i = 0; i < sbox.size();i++){
    V.push_back(hexToBitset(sbox[i]));
  }
}

void setApprox(string ap){
  stringstream res(ap);
  string word;
  Approx temp;
  while(res >> word){
    temp.first = hexToBitset(word[0]);
    temp.second = hexToBitset(word[1]);
    approx.push_back(temp);
  }
}

bitset<4> AND(bitset<4> a, bitset<4> b){
  return a & b;
}

void gueteapprox(ifstream &sbox, ifstream &arx){
  string temp;
  sbox >> temp;
  setV(temp);
  vector<string> a;
  while(arx >> temp){
    a.push_back(temp);
  }
  if(a[1] == "00" || a[5] == "00" || a[9] == "00" || a[11] == "00"){
    cerr << "-1" << endl;
    exit(1);
  }else{
    temp = "";
    temp.append(a[1]);
    temp.append(" ");
    temp.append(a[5]);
    temp.append(" ");
    temp.append(a[9]);
    temp.append(" ");
    temp.append(a[11]);
    temp.append(" ");
    setApprox(temp);
  }

  double T = 1;
  for(size_t i = 0; i < 4; i++){
    double L = 0;
    for(size_t j=0; j < 16; j++){
      bitset<4> u = U[j];
      bitset<4> v = V[j];
      bitset<4> ua =AND(approx[i].first,u);
      bitset<4> vb =AND(approx[i].second,v);
      if((ua[3]^ua[2]^ua[1]^ua[0]^vb[3]^vb[2]^vb[1]^vb[0]) == 0){
        L += 1;
      }
    }
    T *= abs((L-8)/16);
  }
  cout << "T: "<< T << endl;
}
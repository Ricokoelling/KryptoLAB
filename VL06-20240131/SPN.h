#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>

using namespace std;

vector<string> Sbox{"E", "4", "D", "1", "2", "F", "B", "8", "3", "A", "6", "C", "5", "9", "0", "7"};
vector<int> Permutation{0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

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

string XOR(string a, string b){
  if(a.size() != b.size()){
    cerr << "Wrong Size in XOR, string ;" << endl;
    cerr << "a: " << a << " size: " << a.size() << "|| b: "<< b << " size: " << b.size() << endl;
    return a;
  }

  stringstream  res;
  bitset<4> temp;
  string output, subs, subs2;
  for(size_t i=0; i < 4; i++){
    temp = hex_to_bitset(a[i]) ^ hex_to_bitset(b[i]);
    res << hex << temp.to_ulong();
    output.append(res.str());
    res.str("");
  }
  return output;
}

string sbox(string input){
  if(input.size() != 4){
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

string pbox(string input){ 

  if(input.size() != 4){
    return "0";
    cerr << "Wrong Hex size" << endl;
  }
  string output, temp;
  for(const char &i: input){
    temp.append(hex_to_bitset(i).to_string());
  }
  for(size_t i = 0; i <16;i++){
    output += temp[Permutation[i]];
  }
  
  stringstream res;
  string re;
  temp = "";
  for(size_t i = 0; i < 4; i++){
    temp += output[i * 4 + 0];
    temp += output[i * 4 + 1];
    temp += output[i * 4 + 2];
    temp += output[i * 4 + 3];
    res << hex << bitset<4>(temp).to_ulong();
    re.append(res.str());
    res = stringstream();
    temp = "";
  }
  return re;
}

void spn(ifstream &input, ifstream &key, ofstream &output){
  vector<string> block = toBlock(input);
  string KEY;
  key >> KEY;
  string temp, re;
  for(size_t i = 0; i < block.size() -1 ; i++){
    temp = block[i];
    temp = XOR(temp, KEY);
    temp = sbox(temp);
    temp = pbox(temp);
    re.append(temp);
    re.append(" ");
  }
  temp = block[block.size()-1];
  temp = XOR(temp, KEY);
  temp = sbox(temp);
  temp = pbox(temp);
  re.append(temp);

  output << re;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

void print_block(vector<bool> k){

  for(const auto &i: k){
    cout << i;
  }
  cout<< endl;
}

vector<bool> blackbox(vector<bool> block){
  cout << "KRYPT" << endl;
  print_block(block);

  return block;
}

vector<bool> en_blackbox(vector<bool> block){
  cout << "ENKRYPT" << endl;
  print_block(block);

  return block;
}

void ECB(string bitstring, size_t t){
  string substring;
  vector<bool> block(t);
  block.clear();
  for( size_t i = 0; i < bitstring.size() ; i+=t){
    substring = bitstring.substr(i,t);
    
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ;k++){
        block.push_back(0);
      }
    }
    blackbox(block);
    block.clear();
  }
}

void EN_ECB(string bitstring, size_t t){
  string substring;
  vector<bool> block(t);
  block.clear();
  for( size_t i = 0; i < bitstring.size() ; i+=t){
    substring = bitstring.substr(i,t);
    
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ;k++){
        block.push_back(0);
      }
    }
    en_blackbox(block);
    block.clear();
  }
}

vector<bool> XOR(vector<bool> block, vector<bool> iv){
  vector<bool> re;
  for(size_t i = 0; i < block.size();i++){
    re.push_back(block[i] ^ iv[i]);
  }

  return re;
}

void CBC(string bitstring, size_t t, string IV){
  string substring;
  vector<bool> block(t);
  vector<bool> iv(IV.size());
  block.clear();
  iv.clear();

  for(size_t j=0; j < IV.size(); j++){
    iv.push_back(IV[j] - '0');
  }

  for(size_t i=0; i < bitstring.size(); i+=t){
    substring = bitstring.substr(i,t);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }
    block = XOR(block,iv);
    iv.clear();
    iv = blackbox(block);
    block.clear();
  }
}

void EN_CBC (string cypherstring, size_t t, string IV){
  string substring;
  vector<bool> block(t);
  vector<bool> iv(IV.size());
  block.clear();
  iv.clear();

  for(size_t j=0; j < IV.size(); j++){
    iv.push_back(IV[j] - '0');
  }

  for(size_t i=0; i < cypherstring.size(); i+=t){
    substring = cypherstring.substr(i,t);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }
    vector<bool> temp = en_blackbox(block);
    block = XOR(block,iv);
    iv.clear();
    iv = temp;
    block.clear();
  }
}

void OFB(string bitstring, string IV){

  vector<bool> iv(IV.size());
  vector<bool> block(iv.size());
  string substring;

  vector<bool> output;

  const size_t t = iv.size();
  block.clear();
  iv.clear();

  for(size_t j=0; j < IV.size(); j++){
    iv.push_back(IV[j] - '0');
  }

  for(size_t i=0; i < bitstring.size(); i+=t){
    substring = bitstring.substr(i,t);
    iv = blackbox(iv);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }
    output = XOR(block, iv);
    print_block(output);
    block.clear();
  }
}

void EN_OFB(string cypherstring, string IV){
  vector<bool> iv(IV.size());
  vector<bool> block(iv.size());
  string substring;

  vector<bool> output;

  const size_t t = iv.size();
  block.clear();
  iv.clear();

  for(size_t j=0; j < IV.size(); j++){
    iv.push_back(IV[j] - '0');
  }

  for(size_t i=0; i < cypherstring.size(); i+=t){
    substring = cypherstring.substr(i,t);
    iv = en_blackbox(iv);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }
    output = XOR(block, iv);
    print_block(output);
    block.clear();
  }
}

vector<bool> increment(vector<bool> counter, const size_t t){

  for(size_t i = t; i >= 0; i--){
    if(counter[i] == 1){
      counter[i] = 0;
    }else if(counter[i] == 0) {
      counter[i] = 1;
      return counter;
    }else{
      cout << "SOMETHING WENT WRONG AT: " << i << endl; 
      return counter;
    }
  }
}

void CTR(string bitstring){
  vector<bool> counter(8,0); //8bit this time can be more depening on what the user wants 
  vector<bool> block(counter.size());
  vector<bool> output;
  string substring;

  block.clear();
  const size_t t = counter.size();

  for(size_t i=0; i < bitstring.size(); i+=t){
    substring = bitstring.substr(i,t);
    blackbox(counter); //iv = blackbox(iv);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }    
    output = XOR(block, counter);
    counter = increment(counter,t);
    cout << "output: ";
    print_block(output);
    block.clear();
  }
}

void EN_CTR(string cypherstring){
  vector<bool> counter(8,0); //8bit this time can be more depening on what the user wants 
  vector<bool> block(counter.size());
  vector<bool> output;
  string substring;

  block.clear();
  const size_t t = counter.size();

  for(size_t i=0; i < cypherstring.size(); i+=t){
    substring = cypherstring.substr(i,t);
    counter = blackbox(counter);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }    
    output = XOR(block, counter);
    counter = increment(counter,t);
    block.clear();
  }
}
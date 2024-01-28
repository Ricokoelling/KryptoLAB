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

vector<bool> blackbox(vector<bool> block, string key){
  vector<bool> bin_key;
  vector<bool> output;
  for(const auto &i: key){
    bin_key.push_back(i - '0');
  }
  for(size_t i = 0; i < block.size(); i++){
    output.push_back(block[i] ^ bin_key[i]);
  }

  return output;
}

vector<bool> en_blackbox(vector<bool> block, string key){
  vector<bool> bin_key;
  vector<bool> output;
  for(const auto &i: key){
    bin_key.push_back(i - '0');
  }
  for(size_t i = 0; i < block.size(); i++){
    output.push_back(block[i] ^ bin_key[i]);
  }

  return output;
}

string ECB(string bitstring, size_t t, string key){
  string substring;
  string output;
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
    block = blackbox(block, key);
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }
  return output;
}

string EN_ECB(string bitstring, size_t t, string key ){
  string substring;
  string output;
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
    block = en_blackbox(block, key);
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }
  return output;
}

vector<bool> XOR(vector<bool> block, vector<bool> iv){
  vector<bool> re;
  for(size_t i = 0; i < block.size();i++){
    re.push_back(block[i] ^ iv[i]);
  }

  return re;
}

string CBC(string bitstring, size_t t, string IV, string key){
  string substring;
  string output;
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
    iv = blackbox(block, key);
    for(const char &k : iv){
      output += k + '0';
    }
    block.clear();
  }

  return output;
}

string EN_CBC(string cypherstring, size_t t, string IV, string key){
  string substring;
  string output;
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
    
    vector<bool> temp = block;
    block = en_blackbox(block, key);
    block = XOR(block,iv);
    iv.clear();
    iv = temp;
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }
  return output;

}

string OFB(string bitstring, string IV, string key){

  vector<bool> iv(IV.size());
  vector<bool> block(iv.size());
  string substring;

  string output;

  const size_t t = iv.size();
  block.clear();
  iv.clear();

  for(size_t j=0; j < IV.size(); j++){
    iv.push_back(IV[j] - '0');
  }

  for(size_t i=0; i < bitstring.size(); i+=t){
    substring = bitstring.substr(i,t);
    iv = blackbox(iv, key);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }
    block = XOR(block, iv);
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }

  return output;
}

string EN_OFB(string cypherstring, string IV, string key){
  vector<bool> iv(IV.size());
  vector<bool> block(iv.size());
  string substring;
  string output;

  const size_t t = iv.size();
  block.clear();
  iv.clear();

  for(size_t j=0; j < IV.size(); j++){
    iv.push_back(IV[j] - '0');
  }

  for(size_t i=0; i < cypherstring.size(); i+=t){
    substring = cypherstring.substr(i,t);
    iv = en_blackbox(iv, key);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }
    block = XOR(block, iv);
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }

  return output;
}

vector<bool> increment(vector<bool> counter, const size_t t){

  for(size_t i = t - 1; i >= 0; i--){
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

string CTR(string bitstring, string key){
  vector<bool> counter(8,0); //8bit this time can be more depening on what the user wants 
  vector<bool> block(counter.size());
  vector<bool> krypt;
  string substring;
  string output;

  block.clear();
  const size_t t = counter.size();

  for(size_t i=0; i < bitstring.size(); i+=t){
    substring = bitstring.substr(i,t);
    krypt = blackbox(counter, key); //iv = blackbox(iv);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }    
    block = XOR(block, krypt);
    counter = increment(counter,t);
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }
  return output;
}

string EN_CTR(string cypherstring, string key){
  vector<bool> counter(8,0); //8bit this time can be more depening on what the user wants 
  vector<bool> block(counter.size());
  vector<bool> temp;
  string substring;
  string output;

  block.clear();
  const size_t t = counter.size();

  for(size_t i=0; i < cypherstring.size(); i+=t){
    substring = cypherstring.substr(i,t);
    temp = en_blackbox(counter, key);
    for(size_t k=0; k< substring.size(); k++){
      block.push_back(substring[k] - '0');
    }
    if(substring.size() != t){ //fill space with zero 
      for(size_t k = 0; k < t-substring.size() ; k++){
        block.push_back(0);
      }
    }    
    block = XOR(block, temp);
    counter = increment(counter,t);
    for(const char &k : block){
      output += k + '0';
    }
    block.clear();
  }
  return output;
}
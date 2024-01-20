#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char add(char k, char key) {

  k += key-65;
  if(k > 90){
    k -= 26;
  }
  return k;
}

char sub(char k, char key){
  k-= key - 65;

  if(k< 65){
    k+=26;
  }
  int p = key;
  cout << p << endl;
  return k;
}

void vigenere_krypt(ifstream& text, string key, ofstream& k_text){
  int key_length = key.size();
  int key_index = 0;
  string line;
  while(getline(text, line, '\0'))
  {
    for(char k : line){
      if(k < 65 || k > 90){
        k_text << k;
        continue;
      }
      char temp;
      if(key_index < key_length){
        temp = add(k, key[key_index]);
        key_index++;
      }else{
        key_index = 0;
        temp = add(k, key[key_index]);
        key_index++;
      }

      k_text << temp;
    }
  }
}

void vigenere_enkrypt(ifstream& text, string key, ofstream& en_text){
  int key_length = key.size();
  int key_index = 0;
  cout << "key: " << key << " " << "length: " << key_length << endl;
  string line;
  while(getline(text, line, '\0'))
  {
    for(char k : line){
      if(k < 65 || k > 90){
        en_text << k;
        continue;
      }
      char temp;
      if(key_index < key_length){
        temp = sub(k, key[key_index]);
        key_index++;
      }else{
        key_index = 0;
        temp = sub(k, key[key_index]);
        key_index++;
      }
      cout << key_index << endl;

      en_text << temp;
    }
  }
}
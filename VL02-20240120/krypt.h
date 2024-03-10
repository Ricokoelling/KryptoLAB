#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// adds key onto char
char add(char k, char key) {

  k += key-65;
  if(k > 90){
    k -= 26;
  }
  return k;
}

// subtracts the key from a char
char sub(char k, char key){
  k-= key - 65;

  if(k< 65){
    k+=26;
  }
  return k;
}


// enkrypt a text (from a file ) with vigenere and saves the kryptotext in a file
void vigenere_enkrypt(ifstream& text, string key, ofstream& k_text){
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
// dekrypt a text (from a file ) with vigenere and saves the text in a file
void vigenere_dekrypt(ifstream& text, string key, ofstream& de_text){
  int key_length = key.size();
  int key_index = 0;
  string line;
  while(getline(text, line, '\0'))
  {
    for(char k : line){
      if(k < 65 || k > 90){
        de_text << k;
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
      de_text << temp;
    }
  }
}
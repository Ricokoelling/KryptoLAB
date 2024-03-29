#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// adds key onto char 
char add(char k, string key){
  if (k < 65 || k > 90){
    return k;
  }
  k += stoi(key);
  if(k > 90){
    k -= 26;
  }
  return k;
}

// enkrypt a text(from file) and saves it a file
void add_krypt(ifstream& text, string key, ofstream& k_text){

  string line ;
  while(getline(text, line, '\0')){
    for(char k : line){
      if( k != 32){
        char temp = add(k, key);
        switch (temp)
        {
        case 0: break;
        case 1: k_text << "Ä"; 
          break;
        case 2: k_text << "Ö";
          break;
        case 3: k_text << "Ü";
          break;
        case 4: k_text << k;
          break;
        default: k_text << temp;
          break;
        }
      }else{
        k_text << k;
      }
    }
  }
}

//subtract a key from a char 
char sub(char k, string key){

  if (k < 65 || k > 90){
    return k;
  }
  k -= stoi(key);
  if(k < 65){
    k += 26;
  }
  return k;
}
// dekrypt a enkrypted text (from a file) and save it in a file
void sub_krypt(ifstream& text, string key, ofstream& k_text)
{
  string line ;
  while(getline(text, line, '\0')){
    for(char k : line){
      if( k != 32){
        char temp = sub(k, key);
        switch (temp)
        {
        case 0: break;
        case 1: k_text << "Ä"; 
          break;
        case 2: k_text << "Ö";
          break;
        case 3: k_text << "Ü";
          break;
        case 4: k_text << k;
          break;
        default: k_text << temp;
          break;
        }
      }else{
        k_text << k;
      }
    }
  }
}
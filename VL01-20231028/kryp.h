#include <iostream>
#include <fstream>
#include <string>
using namespace std;


char add(char k, string key){
  if (k < 65 || k > 90){
    return k;
  }
  k += stoi(key);
  if(k > 90){
    k -= 26;
  }
  switch (k)
  {
    case -54:   k = 0;
      break;
    case -117:  k = 1;
      break;
    case -99:   k = 2;
      break;
    case -93:   k = 3;
      break;
    case 53:    k = 4;
      break;
    case 51:    k = 4;
      break;
    default: break;
  }
  return k;
}

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

char sub(char k, string key){

  if (k < 65 || k > 90){
    return k;
  }
  k -= stoi(key);
  switch (k)
  {
    case -68:   k = 0;
      break;
    case 125:  k = 1;
      break;
    case -113:   k = 2;
      break;
    case -107:   k = 3;
      break;
    case 37:    k = 4;
      break;
    case 39:    k = 4;
      break;
    default: break;
  }
  if(k < 65 && k > 4){
    k += 26;
  }
  return k;
}

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
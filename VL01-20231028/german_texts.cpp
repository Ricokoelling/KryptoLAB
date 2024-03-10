#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "kryp.h"


using namespace std;

int key_finder(char e){
    int diff = e -  'E' ;
    if(diff > 26){
      diff -= 26;
    } 
    return diff;
}
int haufig(ifstream& text)
{
    string line;
  	unordered_map< char, int> map; //unordered map to find the most occuring letter (german "E")
    while(getline(text, line, '\0')){
      for(char k : line){
        map[k] += 1;
      }
    }
    int max = 0;
    char ch;
    for (auto i : map){
      if(i.second > max){
        max = i.second;
        ch = i.first;
      }
    }
    return key_finder(ch);
}


int main(int argc, char* args[])  // used as c++ .\german_texts.cpp .\kryp.h 
{
  ifstream text;
  ofstream out("Output.txt");
  if(argc == 2){
    if(!text || !out){
      return 0;
    }
    text.open(args[1]);
    string k = to_string(haufig(text));
    text.close(); // reopen read stream so the text can be passed. 
    text.open(args[1]);
    if(out.is_open() && text.is_open()){
      sub_krypt(text, k, out);
    }
  }else if(argc == 1){
    if(!text || !out){
      return 0;
    }
    text.open("sampleEncrypted.txt");
    string k = to_string(haufig(text));
    text.close(); // reopen read stream so the text can be passed. 
    text.open("sampleEncrypted.txt");
    if(out.is_open() && text.is_open()){
      sub_krypt(text, k, out);
    }
  }
  out.close();
  text.close();
  return 0;
}
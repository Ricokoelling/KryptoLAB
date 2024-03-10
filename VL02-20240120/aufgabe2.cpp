#include <iostream>
#include <fstream>
#include <string>
#include "krypt.h"
using namespace std;

int main(int argc, char* argv[])  
{
  ifstream text;
  ofstream k_text;
  if(argc == 3){
    if(!text || !k_text){
      return 0;
    }
    text.open (argv[1]);
    k_text.open(argv[2]);
    string key;
    cout << "Please input key" << endl;
    cin >> key;
    vigenere_dekrypt(text, key ,k_text);
  }else if(argc == 1){
    if(!text || !k_text){
      return 0;
    }
    text.open ("Kryptotext_TAG.txt");
    k_text.open("Klartext.txt");
    string key;
    cout << "Please input key" << endl;
    cin >> key;
    vigenere_dekrypt(text, key ,k_text);
  }


  text.close();
  k_text.close();
  return 0;
}
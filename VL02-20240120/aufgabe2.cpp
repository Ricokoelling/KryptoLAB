#include <iostream>
#include <fstream>
#include <string>
#include "krypt.h"
using namespace std;

int main(int argc, char* argv[])  
{
  ifstream text;
  ofstream k_text;
  if(!text || !k_text){
    return 0;
  }
  text.open (argv[1]);
  k_text.open(argv[2]);
  string key ;
  cout << "Please input key" << endl;
  cin >> key;
  vigenere_enkrypt(text, key ,k_text);
  
  k_text.close();
  return 0;
}
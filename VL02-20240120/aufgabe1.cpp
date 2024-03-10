#include <iostream>
#include <fstream>
#include <string>
#include "krypt.h"
using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream text;
  ofstream k_text;
  if(argc == 4){
    if(!text || !k_text){
      return 0;
    }
    text.open (argv[1]);
    k_text.open(argv[3]);
    vigenere_enkrypt(text, argv[2] ,k_text);
  }else if(argc == 1){
    if(!text || !k_text){
      return 0;
    }
    text.open ("Klartext_1.txt");
    k_text.open("Output.txt");
    vigenere_enkrypt(text, "TAG" ,k_text);
  }
  

  text.close();
  k_text.close();
  return 0;
}
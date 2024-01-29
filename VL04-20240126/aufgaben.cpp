#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> 
#include "AES.h"
using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream text, roundkey, subbytes,invsubbytes, krypt_text;

  text.open ("Beispiel_1_Klartext.txt");
  krypt_text.open("Beispiel_1_Kryptotext.txt");
  roundkey.open("Beispiel_key.txt");
  subbytes.open("SBox.txt");
  invsubbytes.open("SBoxInvers.txt");

  if(!text || !roundkey ||!subbytes || !invsubbytes || !krypt_text){
    return 0;
  }
  //init(text, roundkey, subbytes);
  inv_init(krypt_text, roundkey, invsubbytes);
  
  text.close();
  roundkey.close();
  subbytes.close();
  invsubbytes.close();
  krypt_text.close();
  return 0;
}


#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> 
#include "AES.h"
using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream text, roundkey, subbytes , invsub;
  text.open ("Klartext.txt");
  roundkey.open("key.txt");
  invsub.open("SBoxInvers.txt");
  subbytes.open("SBox.txt");

  if(!text || !roundkey ||!subbytes ){
    return 0;
  }
  string IV("00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
  ECB(text,roundkey, subbytes);


  text.close();
  roundkey.close();
  subbytes.close();
  return 0;
}


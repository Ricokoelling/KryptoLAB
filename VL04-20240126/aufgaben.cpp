#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> 
#include "AES.h"

using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream text, roundkey, subbytes;
  ofstream k_text;
  if(!text || !k_text){
    return 0;
  }
  text.open (argv[1]);
  roundkey.open(argv[2]);
  subbytes.open(argv[3]);
  init(text, roundkey, subbytes);
  
  text.close();
  roundkey.close();
  subbytes.close();
  return 0;
}


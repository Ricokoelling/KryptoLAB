#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> 
#include "AES.h"

using namespace std;

bitset<8> kekw(bitset<8> test){
  bitset<8> b("00011011");
  bitset<8> output = test<<1;
  if(test[7]){
    return output ^= b; 
  }else{
    return output;
  }

}
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


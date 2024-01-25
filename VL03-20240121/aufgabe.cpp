#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "betriebsmodi.h"

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
  string bitstring;
  while(getline(text, bitstring, '\0'))
  {
    ECB(bitstring, 8);
  }
  text.close();
}

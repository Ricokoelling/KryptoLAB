#include <iostream>
#include <fstream>
#include <string>
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
  ECB(128, text, k_text);
}

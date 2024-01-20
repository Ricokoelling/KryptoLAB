#include <iostream>
#include <fstream>
#include <string>
#include "kryp.h"
using namespace std;

int main(int argc, char* argv[])  // used as .\a.exe .\Verschluesseltertext.txt key .\Klartext.txt
{
  ifstream text;
  ofstream k_text;
  if(!text || !k_text){
    return 0;
  }
  text.open (argv[1]);
  k_text.open(argv[3]);
  sub_krypt(text, argv[2] ,k_text);
  k_text.close();
  return 0;
}
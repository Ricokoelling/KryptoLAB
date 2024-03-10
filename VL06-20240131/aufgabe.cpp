#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>
#include "SPN.h"
#include "ExampleTexts.h"


using namespace std;

main(int argc, char* argv[])
{
  ofstream klartext;

  klartext.open("klartext.txt"); 

  RandomHex(klartext, 4000);

  klartext.close();

  ifstream klartext_spn, key;
  ofstream output;

  klartext_spn.open("klartext.txt");
  key.open("key.txt");
  output.open("crypttext.txt");
  spn(klartext_spn,key,output);
  klartext_spn.close();
  key.close();
  output.close();

  return 0;
}
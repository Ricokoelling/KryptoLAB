#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>
#include "LinApprox.h"
#include "ExampleTexts.h"


using namespace std;

main(int argc, char* argv[])
{
  ofstream klartext;

  klartext.open("klartext.txt");

  RandomHex(klartext, 4000);

  klartext.close();

  ifstream input, klartext_spn;
  ofstream output;

  input.open("klartext.txt");
  klartext_spn.open("crypttext.txt");
  init(input, klartext_spn);
  input.close();
  klartext_spn.close();

  return 0;
}
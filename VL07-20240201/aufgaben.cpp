#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>
#include "gueteapprox.h"

using namespace std;

main(int argc, char* argv[])
{
  ifstream sbox, approx;

  sbox.open(argv[1]); // "Beispiel_SBox.txt"
  approx.open(argv[2]); // "Beispiel_Approximation.txt"
  gueteapprox(sbox,approx);
  return 0;
}
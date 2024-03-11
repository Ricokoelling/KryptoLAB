#include <iostream>
#include <gmpxx.h>
#include <limits.h>
#include <cmath>
#include <string>
#include "SHA3.h"

using namespace std;
int main(int argc, char* argv[]){
  
  ifstream input;
  ofstream output;
  input.open(argv[1]);
  output.open(argv[2]);

  sha3(input, output);

  return 0;
}
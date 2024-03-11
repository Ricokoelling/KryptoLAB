#include <iostream>
#include <gmpxx.h>
#include <limits.h>
#include <cmath>
#include <string>
#include "12SHA3.h"

using namespace std;
int main(int argc, char* argv[]){
  
  ifstream input; 
  ofstream output;
  input.open(argv[1]);
  output.open(argv[2]);
  exec(input, output);

  input.close();
  output.close();
  return 0;
}
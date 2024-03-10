#include <iostream>
#include <gmpxx.h>
#include <limits.h>
#include "RSA.h"

using namespace std;
int main(){

  ifstream input, key;
  ofstream output;
  input.open("ExampleText.txt");
  key.open("ExampleKey.txt");
  output.open("output.txt");

  RSA(input,key, output);

  input.close();
  key.close();
  output.close();

  return 0;
}


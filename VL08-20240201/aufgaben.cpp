#include <iostream>
#include <gmpxx.h>
#include <limits.h>
#include "RSA.h"

using namespace std;
int main(){

  ifstream input, key;
  input.open("ExampleText.txt");
  key.open("ExampleKey.txt");

  RSA(input,key);

  return 0;
}


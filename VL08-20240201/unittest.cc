#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>
#include <cassert>
#include "RSA.h"

using namespace std;

main(){
  ifstream input, key;
  ofstream output;
  input.open("ExampleText.txt");
  key.open("ExampleKey.txt");
  output.open("output.txt");

  RSA(input,key, output);

  input.close();
  key.close();
  output.close();

  ifstream test1, test2;
  test1.open("ExampleEncrypted.txt");
  test2.open("output.txt");

  cout << "Run all tests: " << endl;

  string test1_str, test2_str;
  getline(test1, test1_str, '\0');
  getline(test2, test2_str, '\0');
  assert(test1_str == test2_str);
  cout << "All tests passed!" << endl;
}
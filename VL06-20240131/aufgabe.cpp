#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>
//#include "SPN.h"
#include "LinApprox.h"


using namespace std;

main(int argc, char* argv[])
{
  ifstream input, key, output;

  input.open("klartext.txt");
  key.open("key.txt");

  output.open("output.txt");

  init(input, output );

/*
TODO: 

Text generation idk 
*/

  return 0;
}
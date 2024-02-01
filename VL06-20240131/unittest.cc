#include <cassert>
#include <iostream>
#include <bitset>
#include "LinApprox.h"
#include "ExampleTexts.h"
//#include "SPN.h" // not in bc double declaration 

using namespace std;

main()
{
  ofstream klartext;

  klartext.open("klartext.txt");

  RandomHex(klartext, 4000);

  klartext.close();
  ifstream klartext_spn, key, input;
  ofstream output;

  /*klartext_spn.open("klartext.txt");
  key.open("key.txt");
  output.open("crypttext.txt");
  spn(klartext_spn,key,output);
  klartext_spn.close();
  key.close();
  output.close();*/

  input.open("klartext.txt");
  klartext_spn.open("crypttext.txt");
  init(input, klartext_spn);
  input.close();
  klartext_spn.close();

  remove("klartext.txt");
  remove("crypttext.txt");


  return 0;
}
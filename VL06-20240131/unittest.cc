#include <cassert>
#include <iostream>
#include <bitset>
#include "LinApprox.h"

using namespace std;

main()
{
  ifstream input, cinput;
  input.open("klartext.txt");
  cinput.open("output.txt");

  vector<string> block = toBlock(input);
  vector<string> cblock = toBlock(cinput);

  maxkey MAXKEY;
  int array[256] = {0};
  string v2, v4, u2, u4;
  v2 = XOR("0", cblock[0].substr(1,1)); assert(v2 == "0");
  v4 = XOR("0", cblock[0].substr(3,1)); assert(v4 == "3");
  u2 = invsbox(v2); assert(u2 == "e");
  u4 = invsbox(v4); assert(u4 == "8");
  if(alpha(block[0],u2,u4)){
    cout << "cunt" << endl;
  } 


}
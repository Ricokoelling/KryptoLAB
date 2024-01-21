#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "betriebsmodi.h"

using namespace std;


int main(int argc, char* argv[]) 
{
  ifstream text;
  ofstream k_text;
  if(!text || !k_text){
    return 0;
  }
  text.open (argv[1]);
  k_text.open(argv[2]);
  ECB(32, text, k_text);

  /*vector<bool> k;
  vector<char> block;
  block.push_back('A');

  bitset<8> one_char;
    for(const char &c: block){
      one_char = c;
      cout << one_char << endl;
      for(int i = one_char.size() - 1; i >= 0; i--){
        k.push_back(one_char[i]);
      }
    }


    for (const auto &i : k){
      cout << i;
    }
    cout << endl;

    bitset<8> out;
    size_t count = out.size() - 1;
    for(const auto &i: k){
      out[count] = i;
      cout << i << " " << out << endl;
      count--;
    }
    cout << endl;
    cout << out << endl;
    char gout = out.to_ullong();
    cout << gout;*/
}

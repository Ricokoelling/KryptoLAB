#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> 
#include "AES.h"
using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream text, roundkey, subbytes,invsubbytes, krypt_text;
  ofstream output;

  if(argc == 1){
    text.open ("Beispiel_1_Klartext.txt");
    krypt_text.open("Beispiel_1_Kryptotext.txt");
    roundkey.open("Beispiel_key.txt");
    subbytes.open("SBox.txt");
    invsubbytes.open("SBoxInvers.txt");
    output.open("output.txt");
  }
  else if(argc==3)
  {
    if(argv[1] == "e")
    {
      text.open(argv[2]);
    }else if(argv[1] == "d")
    {
      krypt_text.open(argv[2]);
    }
    roundkey.open(argv[3]);
    output.open(argv[4]);
  }

  if(!text || !roundkey ||!subbytes || !invsubbytes || !krypt_text || !output){
    return 0;
  }

  vector<vector<bitset<8>>> matrix;
  string aes;
  cout << "Do you want to enkrypt or dekrypt?" << endl;
  cout << "(e/d)?" << endl;
  cin >> aes;
  if(aes == "e")
  {
    matrix = init(text, roundkey, subbytes);
  }else if(aes== "d")
  {
    matrix = inv_init(krypt_text, roundkey, invsubbytes);
  }
  stringstream res;
  for(size_t i= 0; i < 4; i++){
    for(size_t j= 0; j < 4; j++){
      res << hex << matrix[i][j].to_ulong();
      output << res.str();
      res.str("");
    }
    cout << endl;
  }

  text.close();
  roundkey.close();
  subbytes.close();
  invsubbytes.close();
  krypt_text.close();
  output.close();
  return 0;
}


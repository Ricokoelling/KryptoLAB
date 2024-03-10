#include <iostream>
#include <fstream>
#include <string>
#include "kryp.h"
using namespace std;

int main(int argc, char* argv[])
{
  ifstream text;
  ofstream k_text;
  if(argc == 4 ){ // used as custom inputs // used as e.g. .\a.exe .\Verschluesseltertext.txt 7 .\Klartext.txt
    text.open (argv[1]);
    k_text.open(argv[3]);
    if(!text || !k_text){
      return 0;
    }
  sub_krypt(text, argv[2] ,k_text);
  }else if(argc == 1){
    cout << "hey" << endl;
    text.open("Kryptotext_1_Key_7.txt");
    k_text.open("Klartext.txt");
    if(!text || !k_text){
      return 0;
    }
    sub_krypt(text, "7" ,k_text);
  }
  text.close();
  k_text.close();
  return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> 
#include "AES.h"
using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream text,ciphertext, roundkey, subbytes , invsub, iv;
  ofstream output;

  invsub.open("SBoxInvers.txt");
  subbytes.open("SBox.txt");
  string IV("00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
  if(!invsub || !subbytes){
    cerr << "No SUBBYTES found in files" << endl;
    EXIT_FAILURE;
  }
  string input;
  if(argc == 1){
    text.open ("Beispiel_1_Klartext.txt");
    roundkey.open("key.txt");
    ciphertext.open("Beispiel_1_Kryptotext.txt");
    output.open("output.txt");
    if(!text || !roundkey || !ciphertext || !output){
      cerr << "Files are missing" << endl;
      EXIT_FAILURE;
    }
    cout << "Do you want to encrypt or decrypt?" << endl;
    cout << "(e/d)?" << endl;
    cin >> input ;
    cin.clear();
    if(input == "e"){
      cout << "Which \"Betriebsmodi\" do you want use? " << endl;
      cout << "(ECB/CBC/OFB/CTR)" << endl;
      cin >> input;
      if(input == "ECB"){
        ECB(text,roundkey, subbytes, output);
      }else if(input == "CBC"){
        CBC(text,roundkey, subbytes, IV, output);
      }else if(input == "OFB"){
        OFB(text,roundkey, subbytes, IV, output);
      }else if(input == "CBC"){
        CTR(text,roundkey, subbytes, IV, output);
      }
    }else if(input == "d"){
      cout << "Which \"Betriebsmodi\" do you want use? " << endl;
      cout << "(ECB/CBC/OFB/CTR)" << endl;
      cin >> input;
      if(input == "ECB"){
        De_ECB(ciphertext,roundkey, subbytes,invsub, output);
      }else if(input == "CBC"){
        De_CBC(ciphertext,roundkey, subbytes,invsub, IV, output);
      }else if(input == "OFB"){
        De_OFB(ciphertext,roundkey, subbytes,invsub, IV, output);
      }else if(input == "CBC"){
        De_CTR(ciphertext,roundkey, subbytes,invsub, IV, output);
      }
    }
  }


  if(argc == 5 || argc == 6){
    input = argv[1];
    if((argc == 5 && input == "ECB" )||  (argc == 6 && input == "ECB" ) || (argc == 5 && input == "De_ECB" )||  (argc == 6 && input == "De_ECB" )){
      text.open(argv[2]);
      roundkey.open(argv[3]);
      output.open(argv[4]);
      if(!text || !roundkey || !output){
        cerr << "Files not in System!" << endl;
        EXIT_FAILURE;
      }
      if(input == "ECB"){
        ECB(text,roundkey, subbytes, output);
      }else if(input == "De_ECB"){
        De_ECB(text,roundkey, subbytes, invsub, output);
      }
    }else if(argc == 5 && input != "ECB"){
      cerr << "Missing IV!" << endl;
      EXIT_FAILURE;
    }else{
      text.open(argv[2]);
      roundkey.open(argv[3]);
      output.open(argv[4]);
      iv.open(argv[5]);
      if(!text || !roundkey || !output ||!iv){
        cerr << "Files not in System!" << endl;
        EXIT_FAILURE;
      }
      getline(iv, IV, '\0');
      if(input == "CBC"){
        CBC(text,roundkey, subbytes, IV, output);
      }else if(input == "OFB"){
        OFB(text,roundkey, subbytes, IV, output);
      }else if(input == "CBC"){
        CTR(text,roundkey, subbytes, IV, output);
      }else if(input == "De_CBC"){
        De_CBC(ciphertext,roundkey, subbytes,invsub, IV, output);
      }else if(input == "De_OFB"){
        De_OFB(ciphertext,roundkey, subbytes,invsub, IV, output);
      }else if(input == "De_CBC"){
        De_CTR(ciphertext,roundkey, subbytes,invsub, IV, output);
      }
    }
  }

  ciphertext.close();
  text.close();
  roundkey.close();
  subbytes.close();
  return 0;
}


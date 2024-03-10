#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "betriebsmodi.h"

using namespace std;


int main(int argc, char* argv[]) 
{
  string bitstring_1 = "10010110"; //8bit
  string bitstring_2 = "1001111010"; // 10 bit
  string bitstring_3 = "011001100110"; // 12 bit
  string bitstring_4 = "0110011001100101"; //16 bit
  string output;
  const string KEY = "01010001"; 
  const string IV = "00000000";
  
  const size_t t = 8; //using 8 bit 

  output = ECB(bitstring_2, t, KEY);
  cout << "ECB Enkrypt: " << output << endl;
  output = DE_ECB(output,t,KEY);
  cout << "ECB Dekrypt: " << output << endl;

  cout << endl;
  output = CBC(bitstring_4, t, IV, KEY); 
  cout << "CBC Enkrypt: " << output << endl;
  output = DE_CBC(output,t, IV,KEY);
  cout << "CBC Dekrypt: " << output << endl;

  cout << endl;
  output = OFB(bitstring_4, IV, KEY); 
  cout << "OFB Enkrypt: " << output << endl;
  output = DE_OFB(output, IV, KEY); 
  cout << "OFB Dekrypt: " << output << endl;

  cout << endl;
  output = CTR(bitstring_4, KEY);
  cout << "CTR Enkrypt: " << output << endl;
  output = DE_CTR(output, KEY);
  cout << "CTR Dekrypt: " << output << endl;

  system("PAUSE");
}

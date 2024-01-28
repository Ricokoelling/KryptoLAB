#include <cassert>
#include <iostream>
#include <sstream>
#include "betriebsmodi.h"

using namespace std;

main()
{
  cout << "Running all Tests: " << endl;

  string bitstring_1 = "10010110"; //10010110 || 8bit
  string bitstring_2 = "1001111010"; // 10011110 10 || 10 bit
  string bitstring_3 = "011001100110"; //01100110 0110 || 12 bit
  string bitstring_4 = "0110011001100101"; //01100110 01100101 || 16 bit
  string bitstring_5 = "01100110011001011001011010010110"; //01100110 01100101 10010110 10010110 32 bit
  const string KEY = "01010001"; 
  const string IV = "00000000";
  const size_t t = 8; //using 8 bit 
  size_t counter = 0; 

  // TEST ECB
  cout << "Test ECB ->" << endl;
  string output1 = ECB(bitstring_1, t, KEY); 
  string output2 = ECB(bitstring_2, t, KEY);
  string output3 = ECB(bitstring_3, t, KEY);
  string output4 = ECB(bitstring_4, t, KEY); 
  string output5 = ECB(bitstring_5, t, KEY);

  assert(output1 == "11000111");                          cout << "run test: " << ++counter << endl;
  assert(output2 == "1100111111010001");                  cout << "run test: " << ++counter << endl;
  assert(output3 == "0011011100110001");                  cout << "run test: " << ++counter << endl;
  assert(output4 == "0011011100110100");                  cout << "run test: " << ++counter << endl;
  assert(output5 == "00110111001101001100011111000111");  cout << "run test: " << ++counter << endl;

  //Test En_ECB 
  cout << "Test EN_ECB -> " << endl;
  output1 = EN_ECB(output1,t, KEY);
  output2 = EN_ECB(output2,t, KEY);
  output3 = EN_ECB(output3,t, KEY);
  output4 = EN_ECB(output4,t, KEY);
  output5 = EN_ECB(output5,t, KEY);

  assert(output1 == bitstring_1);              cout << "run test: " << ++counter << endl;
  assert(output2 == bitstring_2 + "000000");   cout << "run test: " << ++counter << endl;
  assert(output3 == bitstring_3 + "0000");     cout << "run test: " << ++counter << endl;
  assert(output4 == bitstring_4);              cout << "run test: " << ++counter << endl;
  assert(output5 == bitstring_5);              cout << "run test: " << ++counter << endl;

  //Test CBC
  cout << "Test CBC -> " << endl;
  output1 = CBC(output1,t,IV, KEY);
  output2 = CBC(output2,t,IV, KEY);
  output3 = CBC(output3,t,IV, KEY);
  output4 = CBC(output4,t,IV, KEY);
  output5 = CBC(output5,t,IV, KEY);

  assert(output1 == "11000111");                          cout << "run test: " << ++counter << endl;
  assert(output2 == "1100111100011110");                  cout << "run test: " << ++counter << endl;
  assert(output3 == "0011011100000110");                  cout << "run test: " << ++counter << endl;
  assert(output4 == "0011011100000011");                  cout << "run test: " << ++counter << endl;
  assert(output5 == "00110111000000111100010000000011");  cout << "run test: " << ++counter << endl;

  //Test En_CBC
  cout << "test EN_CBC ->" << endl;
  output1 = EN_CBC(output1,t,IV, KEY);
  output2 = EN_CBC(output2,t,IV, KEY);
  output3 = EN_CBC(output3,t,IV, KEY);
  output4 = EN_CBC(output4,t,IV, KEY);
  output5 = EN_CBC(output5,t,IV, KEY);

  assert(output1 == bitstring_1);             cout << "run test: " << ++counter << endl;
  assert(output2 == bitstring_2 + "000000");  cout << "run test: " << ++counter << endl;
  assert(output3 == bitstring_3 + "0000");    cout << "run test: " << ++counter << endl;
  assert(output4 == bitstring_4);             cout << "run test: " << ++counter << endl;
  assert(output5 == bitstring_5);             cout << "run test: " << ++counter << endl;

  //Test OFB
  cout << "Test OFB ->" << endl;
  output1 = OFB(output1,IV, KEY);
  output2 = OFB(output2,IV, KEY);
  output3 = OFB(output3,IV, KEY);
  output4 = OFB(output4,IV, KEY);
  output5 = OFB(output5,IV, KEY);

  assert(output1 == "11000111");                          cout << "run test: " << ++counter << endl;             
  assert(output2 == "1100111110000000");                  cout << "run test: " << ++counter << endl;
  assert(output3 == "0011011101100000");                  cout << "run test: " << ++counter << endl;
  assert(output4 == "0011011101100101");                  cout << "run test: " << ++counter << endl; 
  assert(output5 == "00110111011001011100011110010110");  cout << "run test: " << ++counter << endl;

  //Test EN_OFB
  cout << "Test En_OFB->" << endl;
  output1 = EN_OFB(output1,IV, KEY);              
  output2 = EN_OFB(output2,IV, KEY);
  output3 = EN_OFB(output3,IV, KEY);
  output4 = EN_OFB(output4,IV, KEY);
  output5 = EN_OFB(output5,IV, KEY);

  assert(output1 == bitstring_1);             cout << "run test: " << ++counter << endl;
  assert(output2 == bitstring_2 + "000000");  cout << "run test: " << ++counter << endl;
  assert(output3 == bitstring_3 + "0000");    cout << "run test: " << ++counter << endl;
  assert(output4 == bitstring_4);             cout << "run test: " << ++counter << endl;
  assert(output5 == bitstring_5);             cout << "run test: " << ++counter << endl;

  //Test CTR
  cout << "Test CTR ->" << endl;
  output1 = CTR(output1, KEY);
  output2 = CTR(output2, KEY);
  output3 = CTR(output3, KEY);
  output4 = CTR(output4, KEY);
  output5 = CTR(output5, KEY);

  assert(output1 == "11000111");                          cout << "run test: " << ++counter << endl;
  assert(output2 == "1100111111010000");                  cout << "run test: " << ++counter << endl;
  assert(output3 == "0011011100110000");                  cout << "run test: " << ++counter << endl;
  assert(output4 == "0011011100110101");                  cout << "run test: " << ++counter << endl;
  assert(output5 == "00110111001101011100010111000100");  cout << "run test: " << ++counter << endl;


  //Test EN_CTR
  cout << "Test EN_CTR -> " << endl;
  output1 = EN_CTR(output1, KEY);
  output2 = EN_CTR(output2, KEY);
  output3 = EN_CTR(output3, KEY);
  output4 = EN_CTR(output4, KEY);
  output5 = EN_CTR(output5, KEY);

  assert(output1 == bitstring_1);               cout << "run test: " << ++counter << endl;
  assert(output2 == bitstring_2 + "000000");    cout << "run test: " << ++counter << endl;
  assert(output3 == bitstring_3 + "0000");      cout << "run test: " << ++counter << endl;
  assert(output4 == bitstring_4);               cout << "run test: " << ++counter << endl;
  assert(output5 == bitstring_5);               cout << "run test: " << ++counter << endl;

  
 cout << "All tests passed! Total number of test: " << counter << endl;
}
#include <cassert>
#include <bitset>
#include <iostream>
#include <vector>

#include "AES.h"

using namespace std;

main()
{
  cout << "Starting all Tests: " << endl;
  size_t counter = 0;
  ifstream input, keys, sbox, krypttext;

  input.open("Beispiel_1_Klartext.txt");
  keys.open("Beispiel_key.txt");
  sbox.open("SBox.txt");
  krypttext.open("Beispiel_1_Kryptotext.txt");

  //Test Hex to bitset
  assert(hex_to_bitset("00") == bitset<8>("00000000")); cout << "run test: " << ++counter << endl; // 1
  assert(hex_to_bitset("11") == bitset<8>("00010001")); cout << "run test: " << ++counter << endl; // 2 
  assert(hex_to_bitset("5a") == bitset<8>("01011010")); cout << "run test: " << ++counter << endl; // 3
  assert(hex_to_bitset("ee") == bitset<8>("11101110")); cout << "run test: " << ++counter << endl; // 4
  assert(hex_to_bitset("ff") == bitset<8>("11111111")); cout << "run test: " << ++counter << endl; // 5

  vector<vector<bitset<8>>> matrix;
  //Test to_Block
  matrix = to_block(input);
  bitset<8> m1("01011100"); bitset<8> m5("00101100"); bitset<8> m9("10111010");  bitset<8> m13("11000100");
  bitset<8> m2("11110110"); bitset<8> m6("11011111"); bitset<8> m10("00101011"); bitset<8> m14("00011010");
  bitset<8> m3("11101110"); bitset<8> m7("00000101"); bitset<8> m11("01100011"); bitset<8> m15("01011111");
  bitset<8> m4("01111001"); bitset<8> m8("11100001"); bitset<8> m12("00100101"); bitset<8> m16("00010000");
  vector<vector<bitset<8>>> matrix_eq{{m1,m5, m9, m13}, 
                                 {m2,m6, m10, m14},
                                 {m3,m7, m11, m15},
                                 {m4,m8, m12, m16}}; 
  assert(matrix == matrix_eq); cout << "run test: " << ++counter << endl; //6 

  //Test to_vecstring
  vector<string> key;
  key = to_vecstring(keys);
  
  vector<string> key_eq;
  key_eq.push_back("2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c");
  key_eq.push_back("a0 fa fe 17 88 54 2c b1 23 a3 39 39 2a 6c 76 05");
  key_eq.push_back("f2 c2 95 f2 7a 96 b9 43 59 35 80 7a 73 59 f6 7f");
  key_eq.push_back("3d 80 47 7d 47 16 fe 3e 1e 23 7e 44 6d 7a 88 3b");
  key_eq.push_back("ef 44 a5 41 a8 52 5b 7f b6 71 25 3b db 0b ad 00");
  key_eq.push_back("d4 d1 c6 f8 7c 83 9d 87 ca f2 b8 bc 11 f9 15 bc");
  key_eq.push_back("6d 88 a3 7a 11 0b 3e fd db f9 86 41 ca 00 93 fd");
  key_eq.push_back("4e 54 f7 0e 5f 5f c9 f3 84 a6 4f b2 4e a6 dc 4f");
  key_eq.push_back("ea d2 73 21 b5 8d ba d2 31 2b f5 60 7f 8d 29 2f");
  key_eq.push_back("ac 77 66 f3 19 fa dc 21 28 d1 29 41 57 5c 00 6e");
  key_eq.push_back("d0 14 f9 a8 c9 ee 25 89 e1 3f 0c c8 b6 63 0c a6");

  cout << "run test: " << ++counter << endl; // 7
  for(size_t i=0; i < key.size(); i++){
    assert(key[i] == key_eq[i]); 
  }
  // Test to_byte
  vector<vector<string>> bytes;
  bytes = to_bytes(sbox);

  vector<vector<string>> bytes_eq{{"63","7c","77","7b","f2","6b","6f","c5","30","01","67","2b","fe","d7","ab","76"},
                                  {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
                                  {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
                                  {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
                                  {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
                                  {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
                                  {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
                                  {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
                                  {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
                                  {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
                                  {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
                                  {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
                                  {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
                                  {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
                                  {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
                                  {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"},};
  cout << "run test: " << ++counter << endl; // 8
  for(size_t i= 0; i< 16; i++){
    for(size_t j = 0; j< bytes[i].size() - 1;j++){
      assert(bytes[i][j] == bytes_eq[i][j]);
    }
  }

  //Test add_roundkey

  bitset<8> n1("01110111"); bitset<8> n5("00000100"); bitset<8> n9("00010001");  bitset<8> n13("11001101");
  bitset<8> n2("10001000"); bitset<8> n6("01110001"); bitset<8> n10("11011100"); bitset<8> n14("11010101");
  bitset<8> n3("11111011"); bitset<8> n7("11010111"); bitset<8> n11("01110110"); bitset<8> n15("00010000");
  bitset<8> n4("01101111"); bitset<8> n8("01000111"); bitset<8> n12("10101101"); bitset<8> n16("00101100");
  vector<vector<bitset<8>>> addroundkey_eq{{n1,n5, n9, n13}, 
                                 {n2,n6, n10, n14},
                                 {n3,n7, n11, n15},
                                 {n4,n8, n12, n16}};
  matrix = add_roundkey(matrix,key[0]);
  assert(matrix == addroundkey_eq); cout << "run test: " << ++counter << endl; // 9

  //Test lookup
  assert(lookup("00", bytes_eq) == bitset<8>("01100011")); cout << "run test: " << ++counter << endl; // 10
  assert(lookup("11", bytes_eq) == bitset<8>("10000010")); cout << "run test: " << ++counter << endl; // 11 
  assert(lookup("ee", bytes_eq) == bitset<8>("00101000")); cout << "run test: " << ++counter << endl; // 12 
  assert(lookup("ff", bytes_eq) == bitset<8>("00010110")); cout << "run test: " << ++counter << endl; // 13 
  assert(lookup("2e", bytes_eq) == bitset<8>("00110001")); cout << "run test: " << ++counter << endl; // 14

  //Test substitute 
  bitset<8> s1("11110101"); bitset<8> s5("11110010"); bitset<8> s9("10000010");  bitset<8> s13("10111101");
  bitset<8> s2("11000100"); bitset<8> s6("10100011"); bitset<8> s10("10000110"); bitset<8> s14("00000011");
  bitset<8> s3("00001111"); bitset<8> s7("00001110"); bitset<8> s11("00111000"); bitset<8> s15("11001010");
  bitset<8> s4("10101000"); bitset<8> s8("10100000"); bitset<8> s12("10010101"); bitset<8> s16("01110001");
  vector<vector<bitset<8>>> sub_eq{{s1,s5, s9, s13}, 
                                 {s2,s6, s10, s14},
                                 {s3,s7, s11, s15},
                                 {s4,s8, s12, s16}};
  matrix = sub(matrix, bytes_eq);
  assert(matrix == sub_eq); cout << "run test: " << ++counter << endl; // 15 

  //Test rowshift
  bitset<8> r1("11110101"); bitset<8> r5("11110010"); bitset<8> r9("10000010");  bitset<8> r13("10111101");
  bitset<8> r2("10100011"); bitset<8> r6("10000110"); bitset<8> r10("00000011"); bitset<8> r14("11000100");
  bitset<8> r3("00111000"); bitset<8> r7("11001010"); bitset<8> r11("00001111"); bitset<8> r15("00001110");
  bitset<8> r4("01110001"); bitset<8> r8("10101000"); bitset<8> r12("10100000"); bitset<8> r16("10010101");
  vector<vector<bitset<8>>> row_eq{{r1,r5, r9, r13}, 
                                 {r2,r6, r10, r14},
                                 {r3,r7, r11, r15},
                                 {r4,r8, r12, r16}};
  matrix = shiftrows(matrix);                               
  assert(matrix == row_eq); cout << "run test: " << ++counter << endl; // 16

  //Test multi 
  assert(multi(bitset<8>("00000000")) == bitset<8>("00000000")); cout << "run test: " << ++counter << endl; // 17
  assert(multi(bitset<8>("00000001")) == bitset<8>("00000010")); cout << "run test: " << ++counter << endl; // 18 
  assert(multi(bitset<8>("10000001")) == bitset<8>("00011001")); cout << "run test: " << ++counter << endl; // 19 
  assert(multi(bitset<8>("11111111")) == bitset<8>("11100101")); cout << "run test: " << ++counter << endl; // 20

  //Test add  
  assert(add(bitset<8>("00000000"),1) == bitset<8>("00000000")); cout << "run test: " << ++counter << endl; //21 
  assert(add(bitset<8>("11111111"), 1) == bitset<8>("11111111"));cout << "run test: " << ++counter << endl; //22
  assert(add(bitset<8>("10000001"),2) == bitset<8>("00011001")); cout << "run test: " << ++counter << endl; //23 
  assert(add(bitset<8>("10000001"),3) == bitset<8>("10011000")); cout << "run test: " << ++counter << endl; //24

  //Test mamul
  vector<int> gal1{3,2,1,1};
  vector<int> gal2{1,3,2,1};
  vector<int> gal3{1,1,3,2};

  vector<bitset<8>> column{bitset<8>("00000000"), bitset<8>("00001111"),bitset<8>("11111111"),bitset<8>("01100101")};
  assert(mamul(column, gal1) == bitset<8>("10000100")); cout << "run test: " << ++counter << endl; //25
  assert(mamul(column, gal2) == bitset<8>("10010001")); cout << "run test: " << ++counter << endl; //26
  assert(mamul(column, gal3) == bitset<8>("11011111")); cout << "run test: " << ++counter << endl; //27

  //Test mixcolumns
  bitset<8> mc1("01000110 "); bitset<8> mc5("00001100 "); bitset<8> mc9("10110101 ");  bitset<8> mc13("10101101");
  bitset<8> mc2("10010001 "); bitset<8> mc6("00001000 "); bitset<8> mc10("00110101 "); bitset<8> mc14("10101001");
  bitset<8> mc3("10110101 "); bitset<8> mc7("00011000 "); bitset<8> mc11("01100100 "); bitset<8> mc15("11000001");
  bitset<8> mc4("01111101 "); bitset<8> mc8("00001010 "); bitset<8> mc12("11001010 "); bitset<8> mc16("00100111");
  vector<vector<bitset<8>>> mc_eq{{mc1,mc5, mc9, mc13}, 
                                 {mc2,mc6, mc10, mc14},
                                 {mc3,mc7, mc11, mc15},
                                 {mc4,mc8, mc12, mc16}};

  matrix = mixcolumns(matrix);
  assert(matrix == mc_eq); cout << "run test: " << ++counter << endl; //28

  //Test fully 
  ifstream input2, krypttext2, new_input, new_key, new_sbox;
  input2.open("Beispiel_2_Klartext.txt");
  krypttext2.open("Beispiel_2_Kryptotext.txt");

  string input_word, krypto_word;
  stringstream res;
  vector<vector<bitset<8>>> test_matrix;
  new_input.open("Beispiel_1_Klartext.txt");
  new_key.open("Beispiel_key.txt");
  new_sbox.open("SBox.txt");
  test_matrix = init(new_input,new_key, new_sbox);
  ofstream output;
  output.open("output.txt");

  for(size_t i= 0; i < 4; i++){
    for(size_t j= 0; j < 4; j++){
      res << hex << uppercase << matrix[i][j].to_ulong();
      output << res.str();
      res.str("");
    }
  }
  ifstream test_input;
  test_input.open("output.txt");
  while(test_input >> input_word && krypttext >> krypto_word){
    assert(input_word == krypto_word);
  }
  cout << "run test: " << ++counter << endl; //29

  ifstream new_key2,new_sbox2;
  new_key2.open("Beispiel_key.txt");
  new_sbox2.open("SBox.txt");
  matrix = init(input2,new_key2, new_sbox2);
  ofstream output2;
  output2.open("output2.txt");

  for(size_t i= 0; i < 4; i++){
    for(size_t j= 0; j < 4; j++){
      res << hex << uppercase << matrix[i][j].to_ulong();
      output2<< res.str();
      res.str("");
    }
  }
  ifstream test_input2;
  test_input2.open("output.txt");
  while(input2 >> input_word && krypttext2 >> krypto_word){
    assert(input_word == krypto_word);
  }
  cout << "run test: " << ++counter << endl; //30

  //Test invrowshift
  vector<vector<bitset<8>>> inv_row_matrix{{bitset<8>("00000001"),bitset<8>("00000101"), bitset<8>("00001001"), bitset<8>("00001101")}, 
                                           {bitset<8>("00000010"),bitset<8>("00000110"), bitset<8>("00001010"), bitset<8>("00001110")},
                                           {bitset<8>("00000011"),bitset<8>("00000111"), bitset<8>("00001011"), bitset<8>("00001111")},
                                           {bitset<8>("00000100"),bitset<8>("00001000"), bitset<8>("00001100"), bitset<8>("00010000")}};

  vector<vector<bitset<8>>> inv_row_eq{    {bitset<8>("00000001"),bitset<8>("00000101"), bitset<8>("00001001"), bitset<8>("00001101")}, 
                                           {bitset<8>("00001110"),bitset<8>("00000010"), bitset<8>("00000110"), bitset<8>("00001010")},
                                           {bitset<8>("00001011"),bitset<8>("00001111"), bitset<8>("00000011"), bitset<8>("00000111")},
                                           {bitset<8>("00001000"),bitset<8>("00001100"), bitset<8>("00010000"), bitset<8>("00000100")}}; 
  inv_row_matrix = invshiftrows(inv_row_matrix);                             
  assert(inv_row_matrix == inv_row_eq); cout << "run test: " << ++counter << endl; //31

  //inverse mixcolumns needs no testing since it just uses a diffenerent matrix 

  //Test inv fully
  ifstream de_input, de_keys, de_sbox, de_input2, de_eq_1, de_eq_2;
  ofstream de_output, de_output2;
  string de_input_str, de_output_str;
  de_input.open("Beispiel_1_Kryptotext.txt");
  de_keys.open("Beispiel_key.txt");
  de_sbox.open("SBoxInvers.txt");
  de_output.open("de_output.txt");
  de_output2.open("de_output2.txt");

  vector<vector<bitset<8>>> inv_matrix;

  inv_matrix = inv_init(de_input,de_keys,de_sbox);
  for(size_t i= 0; i < 4; i++){
    for(size_t j= 0; j < 4; j++){
      res << hex << uppercase << inv_matrix[i][j].to_ulong();
      de_output<< res.str();
      res.str("");
    }
  }
  ifstream de_test_input;
  de_test_input.open("de_output.txt");
  while(de_test_input >> de_input_str && de_input >> de_output_str  ){
    assert(de_input_str == de_output_str);
  }
  cout << "run test: " << ++counter << endl; //32


  ifstream de_keys2, de_sbox2;
  de_keys2.open("Beispiel_key.txt");
  de_sbox2.open("SBoxInvers.txt");
  de_input2.open("Beispiel_2_Kryptotext.txt");
  inv_matrix = inv_init(de_input2,de_keys2,de_sbox2);
  for(size_t i= 0; i < 4; i++){
    for(size_t j= 0; j < 4; j++){
      res << hex << uppercase << inv_matrix[i][j].to_ulong();
      de_output2<< res.str();
      res.str("");
    }
  }
  ifstream de_test_input2;
  de_test_input2.open("de_output2.txt");
  while(de_test_input >> de_input_str && de_input2 >> de_output_str  ){
    assert(de_input_str == de_output_str);
  }
  cout << "run test: " << ++counter << endl; //33

  //Closing all files
  input2.close(); 
  krypttext2.close(); 
  new_input.close(); 
  new_key2.close(); 
  new_key.close(); 
  new_sbox.close(); 
  new_sbox2.close(); 
  output2.close(); 
  output.close(); 
  test_input.close(); 
  test_input2.close(); 
  de_input.close(); 
  de_input2.close(); 
  de_keys.close(); 
  de_keys2.close(); 
  de_sbox.close(); 
  de_sbox2.close(); 
  de_eq_1.close(); 
  de_eq_2.close(); 
  de_output2.close(); 
  de_output.close(); 
  de_test_input2.close(); 
  de_test_input.close(); 
  input.close();
  keys.close();
  sbox.close();
  krypttext.close();
  
  cout << "All tests passed! Total number of test: " << counter << endl;
}
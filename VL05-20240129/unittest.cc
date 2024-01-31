#include <cassert>
#include <iostream>
#include <bitset>
#include "AES.h"

using namespace std;

main()
{
  cout << "Start all Tests: " << endl;

  ifstream sbox, keys;
  sbox.open("Sbox.txt");
  keys.open("key.txt");
  to_bytes(sbox);

  int counter = 0;
  //Test key gen
  assert("00" == XOR("00", "00")); cout << "run test: "<< ++counter << endl; // 1
  assert("00" == XOR("ff", "ff")); cout << "run test: "<< ++counter << endl; // 2
  assert("ff" == XOR("00", "ff")); cout << "run test: "<< ++counter << endl; // 3
  assert("ff" == XOR("ff", "00")); cout << "run test: "<< ++counter << endl; // 4
  assert("06" == XOR("05", "03")); cout << "run test: "<< ++counter << endl; // 5
  assert("ff" == XOR("5c", "a3")); cout << "run test: "<< ++counter << endl; // 6
  assert("75" == XOR("b2", "c7")); cout << "run test: "<< ++counter << endl; // 7

  vector<bitset<8>> a{bitset<8>("00000000"), bitset<8>("11111111"), bitset<8>("01010101"), bitset<8>("11001011")};
  vector<bitset<8>> b{bitset<8>("00000000"), bitset<8>("11111111"), bitset<8>("01100001"), bitset<8>("01110010")};
  vector<bitset<8>> c{bitset<8>("00000000"), bitset<8>("00000000"), bitset<8>("00110100"), bitset<8>("10111001")};
  assert(c == XOR(a,b)); cout << "run test: "<< ++counter << endl; // 8

  vector<bitset<8>> rcon_test1{bitset<8>("00000001"), bitset<8>("00000000"), bitset<8>("00000000"), bitset<8>("00000000")};
  vector<bitset<8>> rcon_test2{bitset<8>("00011011"), bitset<8>("00000000"), bitset<8>("00000000"), bitset<8>("00000000")};

  assert(rcon_test1 == rCon(0)); cout << "run test: "<< ++counter << endl; // 9
  assert(rcon_test2 == rCon(8)); cout << "run test: "<< ++counter << endl; // 10


  //RotWord test
  string w1 = "ee 5c 01 00";
  vector<bitset<8>> w_eq{bitset<8>("01011100"),bitset<8>("00000001"),bitset<8>("00000000"),bitset<8>("11101110")};
  vector<bitset<8>> temp = RotWord(w1);
  assert(w_eq == RotWord(w1)); cout << "run test: "<< ++counter << endl; // 11

  //Subword
  vector<bitset<8>> sub_eq{bitset<8>("01001010"),bitset<8>("01111100"),bitset<8>("01100011"),bitset<8>("00101000")};
  assert(sub_eq == SubWord(w_eq)); cout << "run test: "<< ++counter << endl; // 12

  //KeyGenMod

  string mod_test("a0 fa fe 17");
  assert(mod_test == keyGenmod("2b 7e 15 16", "09 cf 4f 3c",4)); cout << "run test: "<< ++counter << endl; // 13

  vector<string> test = keyGen(to_vecstring(keys));
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

  for(size_t i = 0 ; i < test.size(); i++){
    assert(test[i] == key_eq[i]);
  } cout << "run test: "<< ++counter << endl; // 14

  cout << "All Tests passed! Total tests: " << counter << endl;
}
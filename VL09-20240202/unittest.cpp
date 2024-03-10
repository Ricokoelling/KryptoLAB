#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>
#include <cassert>
#include "RSAKeyGen.h"

using namespace std;

main(){
  
  cout << "Run all tests:" << endl;
  setSeed();
  int counter = 0;
  mpz_t test1, test2,test3;
  mpz_inits(test1, test2, test3, NULL);

  mpz_set_ui(test1, 7);
  mpz_set_ui(test2, 9);
  mpz_set_ui(test3, 9999991);
  assert(isPrime(test1, 100) == true);
  cout << "cunt" << endl;
   cout << "test: " << counter++ << endl;
  assert(!isPrime(test2, 100)); cout << "test: " << counter++ << endl;
  assert(isPrime(test3, 100)); cout << "test: " << counter++ << endl;

  mpz_t test4, test5,test6;
  mpz_inits(test4, test5, test6, NULL);

  genPrime(1000, test4);
  genPrime(1000, test5);
  genPrime(1000, test6);
  assert(isPrime(test4, 26)); cout << "test: " << counter++ << endl;
  assert(isPrime(test5, 26)); cout << "test: " << counter++ << endl;
  assert(isPrime(test6, 26)); cout << "test: " << counter++ << endl;

  mpz_t test7, test8,a,b,c,d, x,y;
  mpz_inits(test7, test8,a,b,c,d,x,y, NULL);

  mpz_set_ui(a,5);
  mpz_set_ui(b,7);
  mpz_set_ui(c,211);
  mpz_set_ui(d,1231);
  mpz_set_ui(x,24);
  mpz_set_ui(y,258300);

  genPhi(test7,a,b);
  genPhi(test8,c,d);

  assert(mpz_cmp(test7,x)==0); cout << "test: " << counter++ << endl;
  assert(mpz_cmp(test8,y)==0); cout << "test: " << counter++ << endl;


  //Full Test
  ofstream primes, pub, priv;

  primes.open("primes.txt");
  pub.open("public_key.txt");
  priv.open("private_key.txt");

  mpz_t p,q;
  mpz_inits(p,q,NULL);

  genPrime(1000,p);
  genPrime(1000,q);

  genKey(p,q,primes,pub,priv);

  priv.close();
  pub.close();
  primes.close();
  ifstream test_file;
  test_file.open("private_key.txt");
  string  line;
  vector<string> test_str;
  while(test_file >> line){
    test_str.push_back(line);
    if(test_str.size() > 2){
      cout << "Wrong" << endl;
    }
  }
  assert(test_str[0] != test_str[1]); cout << "test: " << counter++ << endl;


  test_file.close();
  mpz_clears(p,q,NULL);
  mpz_clears(test1, test2 , test3,test4, test5, test6, test7, test8,a,b,c,d,x,y,NULL);

  cout << "All tests passed!" << endl;

}
#include <iostream>
#include <gmpxx.h>
#include <limits.h>
#include <cmath>
#include "RSAKeyGen.h"

using namespace std;
int main(){
  ofstream primes, pub, priv;

  primes.open("primes.txt");
  pub.open("public_key.txt");
  priv.open("private_key.txt");

  mpz_t p,q;
  mpz_inits(p,q,NULL);

  genPrime(1000,p);
  genPrime(1000,q);

  genKey(p,q,primes,pub,priv);

  mpz_clears(p,q,NULL);

  return 0;
}
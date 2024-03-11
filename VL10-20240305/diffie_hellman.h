#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>
#include <chrono>

using namespace std;

vector<int> iList ={1,7,11,13,17,19,23,29};

// Seed für den Zufallsgenerator setzen
gmp_randstate_t state;

//sets seed for random number generation
void setSeed(){
  const auto p1 = chrono::system_clock::now();
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, chrono::duration_cast<chrono::seconds>(p1.time_since_epoch()).count()); // gets unix timestamp and sets seed with it
}

//sets M in millerrabin
void setM(mpz_t m, mpz_t k){
  mpz_t res;
  mpz_init(res);
  mpz_mod_ui(res,m,2);
  while(mpz_cmp_ui(res,0) == 0){
    mpz_add_ui(k,k,1);
    mpz_div_ui(m,m,2);
    mpz_mod_ui(res,m,2);
  }
  mpz_clear(res);
}

// returns a random number between lower and upper bound
void random_number_between(mpz_t result, const mpz_t lower_bound, const mpz_t upper_bound) { 
    mpz_t range;
    mpz_init(range);
    mpz_sub(range, upper_bound, lower_bound); 

    mpz_urandomm(result, state, range); 

    mpz_add(result, result, lower_bound);
    
    mpz_clear(range);
}

// millerrabin prim number test
bool primeTest(mpz_t n){
  mpz_t k,m,res,n1;
  mpz_inits(k,m,res,n1,NULL);
  mpz_sub_ui(n1,n,1);
  mpz_set(m,n1);
  setM(m,k);

  // set a and b
  mpz_t a,b,lower_bound;
  mpz_inits(a,b,lower_bound,NULL);
  mpz_set_ui(lower_bound,2);
  random_number_between(a,lower_bound, n);
  mpz_powm(b,a,m,n);
  
  mpz_t resb;
  mpz_inits(resb,NULL);
  mpz_mod(resb,b,n);


  if(mpz_cmp_ui(resb,1) == 0){
    return true;
  }
  int count = mpz_get_si(k);
  for(size_t i = 0; i <= count; i++){
    mpz_mod(resb,b,n);
    if(mpz_cmp(resb,n1) == 0){
      return true;
    }
    mpz_powm_ui(b,b,2,n);
  }

  mpz_clears(k,m,res,n1,resb,a,b,lower_bound,NULL);
  return false;
}

//checks if a number is a prime
bool isPrime(mpz_t n, int rounds){
  for(size_t i =0; i < rounds;i++){
    if(!primeTest(n)){
      return false;
    }
  }
  return true;
}

//generates a primenumber
void genPrime(const size_t length, mpz_t n){
  setSeed();
  mpz_t z, lower, upper,base;
  mpz_inits(z,lower,upper,base,NULL);

  mpz_set_ui(base, 2);

  mpz_pow_ui(lower, base, length-1);
  mpz_pow_ui(upper, base, length);
  mpz_sub_ui(upper,upper,1);
  random_number_between(z,lower,upper);

  int i=0;
  mpz_set_ui(n,0);
  mpz_t first,second;
  mpz_inits(first,second,NULL);

  do{
    int temp = i / iList.size();
    mpz_add_ui(first, z, temp);;
    mpz_set_ui(second, iList[i % iList.size()]);
    mpz_mul_ui(n,first,30);
    mpz_add(n,n,second);
    i++;
  }while (!isPrime(n,100));

  mpz_clears(z, lower, upper,base, first,second,NULL);
}

//generates p = 2*q + 1 with q and p prime
void genP(mpz_t p, size_t keylength){
  mpz_t q;
  mpz_init(q);
  while(true){
    genPrime(keylength,q);
    mpz_mul_ui(p,q,2);
    mpz_add_ui(p,p,1);
    if(isPrime(p,100)){
      break;
    }
  }
  mpz_clear(q); 
}


// calculates a "Erzeuger" Zp for p = 2q + 1
void generator(mpz_t p){
  setSeed();
  mpz_t q,a,low,high,temp,temp2;
  mpz_inits(low,high,temp,q,a,temp2,NULL);

  mpz_set_ui(low,2);
  mpz_sub_ui(high,p,1);

  mpz_sub_ui(q,p,1);
  mpz_fdiv_q_ui(q,q,2);
  while(true){
    random_number_between(a,low,high); 
    mpz_powm(temp, a, q,p); 
    mpz_sub_ui(temp2,p,1); 
    mpz_fdiv_q(temp2,temp2,q); 
    mpz_powm(temp2, a, temp2,p);
    if (mpz_cmp_ui(temp,1) && mpz_cmp_ui(temp2,1)){
      mpz_set(p,a);
      break;
    }
  }

  mpz_clears(low,high,temp,q,temp2,a,NULL);
}

// diffiehellman generation
void diffie(size_t keylength){

  mpz_t p,g,a,b,low,high,A,B,S;
  mpz_inits(p,g,a,b,low,high,A,B,S,NULL);

  genPrime(keylength,p);
  mpz_set(g,p);
  generator(g);
  mpz_set_ui(low,2);
  mpz_sub_ui(high,p,1);

  random_number_between(a,low,high);
  random_number_between(b,low,high);

  mpz_powm(A,g,a,p);
  mpz_powm(B,g,b,p);

  mpz_powm(S,B,a,p);

  cout << "Primzahl: " << p << endl;
  cout << "Generator: " << g << endl;
  cout << "Alice: " << A << endl;
  cout << "Bob: " << B << endl;
  cout << "Geheimnis: " << S << endl;
  mpz_clears(p,g,a,b,low,high,A,B,S,NULL);

}

#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>
#include <chrono>

using namespace std;

vector<int> iList ={1,7,11,13,17,19,23,29};

// Seed for random number generation 
gmp_randstate_t state;

//sets Seed for random number generation 
void setSeed(){
  const auto p1 = chrono::system_clock::now();
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, chrono::duration_cast<chrono::seconds>(p1.time_since_epoch()).count()); // gets unix timestamp and sets seed with it
}

//used for primeTest 
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

// outputs a random number between two bounds
void random_number_between(mpz_t result, const mpz_t lower_bound, const mpz_t upper_bound) {
    mpz_t range;
    mpz_init(range);
    mpz_sub(range, upper_bound, lower_bound); 

    mpz_urandomm(result, state, range); 

    mpz_add(result, result, lower_bound);
    
    
    mpz_clear(range);
}

//Primary primeTest with miller Rabin
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

//checks if a number is Prime 
bool isPrime(mpz_t n, int rounds){
  for(size_t i =0; i < rounds;i++){
    if(!primeTest(n)){
      return false;
    }
  }
  return true;
}

//generates Prime
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

//generates Phi
void genPhi(mpz_t phi, const mpz_t p, const mpz_t q){
  mpz_t p1, q1;
  mpz_inits(p1,q1,NULL);
  mpz_sub_ui(p1,p,1);
  mpz_sub_ui(q1,q,1);

  mpz_mul(phi,p1,q1);

  mpz_clears(p1,q1,NULL);
}

// uses euclid algorithm
void euclid(mpz_t ret, const mpz_t a, const mpz_t b, mpz_t ret2){
  mpz_t d, r0, r1,s0,s1,t0,t1;
  mpz_inits(d, r0, r1,s0,s1,t0,t1,NULL);

  mpz_set(r0,a); 
  mpz_set(r1,b);  
  mpz_set_ui(s0,1); 
  mpz_set_ui(s1,0); 
  mpz_set_ui(t0,0); 
  mpz_set_ui(t1,1); 

  while(true){
    mpz_div(d,r0,r1);

    mpz_mul(d,d,r1);
    mpz_sub(r0,r0,d); 

    mpz_mul(d,d,s1);
    mpz_sub(s0,s0,d); 

    mpz_mul(d,d,t1);  
    mpz_sub(t0,t0,d); 
    if(mpz_cmp_ui(r0,0)==0){
      break;
    }
    mpz_swap(r0,r1);
    mpz_swap(s0,s1);
    mpz_swap(t0,t1);
  }
  mpz_set(ret,r1);
  mpz_set(ret2,s1); 


  mpz_clears(d, r0, r1,s0,s1,t0,t1,NULL);
}

// Key generation
void genKey(mpz_t p,mpz_t q, ofstream &primes, ofstream &pub, ofstream &priv){
  mpz_t n,phi,e, ret, lower, upper,phi1,d;
  mpz_inits(n,ret,phi,e,lower,upper,phi1,d,NULL);
  mpz_mul(n,p,q);

  genPhi(phi,p,q);

  mpz_set_ui(e,65537); //2^16 +1
  mpz_set_ui(lower,3);
  mpz_sub_ui(phi1,phi,1);
  mpz_set(upper,phi1);

  euclid(ret,e,phi,d);
  setSeed();
  while(mpz_cmp_ui(ret,1) != 0){
    random_number_between(e,lower, upper);
    euclid(ret,e,phi,d);
  }
  euclid(ret,e,phi,d);
  mpz_mod(d,d,phi);

  string bk = "\n";
  char *str = mpz_get_str(NULL, 10, p);
  char *str1 = mpz_get_str(NULL, 10, q);
  primes << str;
  primes << bk;
  primes << str1;
  free(str);
  free(str1);
  str = mpz_get_str(NULL, 10, e);
  str1 = mpz_get_str(NULL, 10, n);
  pub << str;
  pub << bk;
  pub << str1;
  free(str);
  free(str1);
  str = mpz_get_str(NULL, 10, d);
  str1 = mpz_get_str(NULL, 10, n);
  priv << str;
  priv << bk;
  priv << str1;
  free(str);
  free(str1);
  mpz_clears(n,phi,e, ret, lower, upper,phi1,d, NULL);
}
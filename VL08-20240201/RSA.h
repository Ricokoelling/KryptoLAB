#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>

using namespace std;

//converts int to binary
string intToBin(mpz_t x){
  string output;
  mpz_t div, res;
  mpz_inits(div,res, NULL);
  mpz_set_ui(div,2);
  while(mpz_cmp_ui(x,0)!=0){
    mpz_mod(res,x,div);
    if(mpz_cmp_ui(res,0)==0){
      output.append("0");
    }else{
      output.append("1");
    }
    mpz_div(res,x,div);
    mpz_set(x,res);
  }
  return output;
}

//RSA multiplikation 
string mult(mpz_t x, mpz_t e, mpz_t n){
  char buffer[5000];
  mpz_t y, res;
  mpz_init(y);
  mpz_init(res);
  mpz_set_ui(y,1);
  string eBin = intToBin(e);
  int eLen = eBin.size();
  for(size_t i=0; i <eLen;i++){
    if(eBin[i] == '1'){ 
      mpz_mul(res,y,x);
      mpz_mod(y,res,n);
    }
    mpz_mul(res,x,x);
    mpz_mod(x,res,n);
  }
  mpz_get_str(buffer,10,y);
  string str(buffer);
  return str;
}

//RSA
void RSA(ifstream &input, ifstream &key, ofstream &output){
  string line;
  mpz_t k1,k2,i;
  string ret;
  mpz_init(k1);
  mpz_init(k2);
  mpz_init(i);
  getline(input, line);
  mpz_init_set_str(i, line.c_str(),10);
  getline(key, line);
  mpz_init_set_str(k1, line.c_str(),10);
  getline(key, line);
  mpz_init_set_str(k2, line.c_str(),10);
  output << mult(i, k1, k2);
}
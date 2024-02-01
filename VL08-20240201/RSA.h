#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <gmpxx.h>

using namespace std;

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
/*
TODO:

at * input doesn't matter 

Find out why
*/
string mult(mpz_t x, mpz_t e, mpz_t n){
  char buffer[5000];
  mpz_t y, res;
  mpz_inits(res,y,NULL);
  mpz_set_ui(y,1);
  string eBin = intToBin(e);
  int eLen = eBin.size();
  cout << eBin[2] << endl;
  for(size_t i=0; i < 2;i++){
    if(eBin[i] == '1'){ //*
      cout << "cunt" << endl;
      mpz_mul(res,y,x);
      mpz_mod(y,res,n);
    }//*
    mpz_mul(res,x,x);
    mpz_mod(x,res,n);
  }
  mpz_get_str(buffer,10,x);
  string str(buffer);
  return str;
}

void RSA(ifstream &input, ifstream &key){
  string line;
  mpz_t k1,k2,i,o;
  string ret;
  mpz_init(o);
  getline(input, line);
  mpz_init_set_str(i, line.c_str(),10);
  getline(key, line);
  mpz_init_set_str(k1, line.c_str(),10);
  getline(key, line);
  mpz_init_set_str(k2, line.c_str(),10);
  ret = mult(i, k1, k2);
  cout << ret << endl;
}
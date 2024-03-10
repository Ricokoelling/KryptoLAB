#include <iostream>
#include <gmpxx.h>
#include <limits.h>
#include <cmath>
#include "diffie_hellman.h"

using namespace std;
int main(){
  
  size_t g = 10;
  diffie(g);

  return 0;
}
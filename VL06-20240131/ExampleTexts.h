#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <bitset>

using namespace std;

// generates Random Hex 
string randomHex(size_t count){
  int N = 256, test;
  stringstream res;
  string output, temp;
  for(size_t i=1; i <= count; i++){
    test = rand() % N;
    res << hex << test;
    temp.append(res.str());
    if(res.str().size() < 2){
      temp.insert(0,"0");
    }
    res = stringstream();
    if(i % 2 == 0){
      output.append(temp);
      output.append(" ");
      res = stringstream();
      temp.clear();
    }
  }

  return output;
}

void RandomHex(ofstream &output, size_t count){
  output << randomHex(count);
}

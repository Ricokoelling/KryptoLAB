#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream> 
using namespace std;
const int N = 4;

vector<vector<int>> encrypt = {{2,3,1,1}, {1,2,3,1},{1,1,2,3},{3,1,1,2}};
vector<vector<int>> decrypt = {{14,11,13,9}, {9,14,11,13},{13,9,14,11},{11,13,9,14}};

//converts hex to 8 bit binary
bitset<8> hex_to_bitset(string hex){
  char re;
  int temp = 0;
  if(hex.size() == 2){
    for(size_t i = 0; i < 2; i++){
      if(hex[i] - '0' > 9){
        temp += (hex[i] - 'a') + 10;
      }else{
        temp += hex[i] - '0';
      }
      if(i == 0 ){
        temp *= 16;
      }
    }
  }
  re = temp;
  return re;
}

// adds roundkey to bitsets in AES
vector<vector<bitset<8>>> add_roundkey(vector<vector<bitset<8>>> matrix, string roundkey){
  stringstream rkey(roundkey);
  string text;
  size_t x = 0;
  size_t y = 0;
  rkey >> text;
  do{
    if(x < 4){
      bitset<8> temp = hex_to_bitset(text);
      matrix[x][y] ^=  temp;
      x++;
    }else{
      x = 0;
      y++;
      bitset<8> temp = hex_to_bitset(text);
      matrix[x][y] ^=  temp;
      x++;
    }
  }while(rkey >> text);
  return matrix;
}

// looks up hex in Subbytes
bitset<8> lookup(string hex, vector<vector<string>> bytes){
  int temp[2];
  if(hex.size() == 2){
    for(size_t i = 0; i < 2; i++){
      if(hex[i] - '0' > 9){
        temp[i] = (hex[i] - 'a') + 10;
      }else{
        temp[i] = hex[i] - '0';
      }
    }
    return hex_to_bitset(bytes[temp[0]][temp[1]]);
  }else{
    if(hex[0] - '0' > 9){
      temp[0] = (hex[0] - 'a') + 10;
    }else{
      temp[0] = hex[0] - '0';
    }
    return hex_to_bitset(bytes[0][temp[0]]);
  }
}

// SUBBYTES in AES
vector<vector<bitset<8>>> sub(vector<vector<bitset<8>>> matrix, vector<vector<string>> bytes){
  string subtring;
  stringstream res; 
  for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
      res.str("");
			res << hex  << matrix[i][j].to_ulong();
      matrix[i][j] = lookup(res.str(), bytes);
    }
  }
  return matrix;
}

// shift rows invers
vector<vector<bitset<8>>> invshiftrows (vector<vector<bitset<8>>> matrix){
  bitset<8> temp;

  temp = matrix[1][0];
  matrix[1][0] = matrix[1][3];
  matrix[1][3] = matrix[1][2];
  matrix[1][2] = matrix[1][1];
  matrix[1][1] = temp;

  temp = matrix[2][0];
  matrix[2][0] = matrix[2][2];
  matrix[2][2] = temp;
  temp = matrix[2][1];
  matrix[2][1] = matrix[2][3];
  matrix[2][3] = temp;

  temp = matrix[3][0];
  matrix[3][0] = matrix[3][1];
  matrix[3][1] = matrix[3][2];
  matrix[3][2] = matrix[3][3];
  matrix[3][3] = temp;

  return matrix;
}

// shift rows in AES
vector<vector<bitset<8>>> shiftrows (vector<vector<bitset<8>>> matrix){
  bitset<8> temp;

  temp = matrix[1][0];
  matrix[1][0] = matrix[1][1];
  matrix[1][1] = matrix[1][2];
  matrix[1][2] = matrix[1][3];
  matrix[1][3] = temp;

  temp = matrix[2][0];
  matrix[2][0] = matrix[2][2];
  matrix[2][2] = temp;
  temp = matrix[2][1];
  matrix[2][1] = matrix[2][3];
  matrix[2][3] = temp;

  temp = matrix[3][0];
  matrix[3][0] = matrix[3][3];
  matrix[3][3] = matrix[3][2];
  matrix[3][2] = matrix[3][1];
  matrix[3][1] = temp;

  return matrix;
}

//doubles 8-Bit input
bitset<8> multi(bitset<8> input){
  bitset<8> b("00011011");
  bitset<8> output = input<<1;
  if(input[7]){
    return output ^= b; 
  }else{
    return output;
  }
}

// multiplies 2 8-bit binarys in galois field
bitset<8> add(bitset<8> column, int gal){
  vector<bitset<8>> a;
  vector<int> b;
  bitset<8> output("00000000");
  while(gal > 1){
    a.push_back(column);
    b.push_back(gal);
    gal /= 2;
    column = multi(column);
  }
  a.push_back(column);
  b.push_back(gal);

  for(size_t i = 0; i < a.size(); i++){
    if(b[i] % 2 != 0){
      output ^= a[i];
    }
  }
  return output;
}
//matrix multiplication in galois field
bitset<8> mamul(vector<bitset<8>> column, vector<int> gal){
  bitset<8> a0 = add(column[0], gal[0]);
  bitset<8> a1 = add(column[1], gal[1]);
  bitset<8> a2 = add(column[2], gal[2]);
  bitset<8> a3 = add(column[3], gal[3]);
  return (a0 ^= a1 ^= a2 ^= a3);
}

//inverse of mixcolumns
vector<vector<bitset<8>>> inv_mixcolumns (vector<vector<bitset<8>>> matrix){
  vector<bitset<8>> col;
  for(size_t i = 0; i < N;i++){
    for(size_t a = 0; a < N; a++){
      col.push_back(matrix[a][i]);
    }
    for(size_t k=0; k <N; k++){
      matrix[k][i] = mamul(col, decrypt[k]);
    }
    col.clear();
  }
  return matrix;
}

// mix the columns of the matrix
vector<vector<bitset<8>>> mixcolumns (vector<vector<bitset<8>>> matrix){
  vector<bitset<8>> col;
  for(size_t i = 0; i < N;i++){
    for(size_t a = 0; a < N; a++){
      col.push_back(matrix[a][i]);
    }
    for(size_t k=0; k <N; k++){
      matrix[k][i] = mamul(col, encrypt[k]);
    }
    col.clear();
  }
  return matrix;
}

// converts a input to a bitset matrix
vector<vector<bitset<8>>> to_block(ifstream &input){
  string text;
  size_t x = 0;
  size_t y = 0;
  vector<vector<bitset<8>>> matrix;
  matrix.resize(N); // 4 Zeilen
  for (int i = 0; i < N; ++i) {
    matrix[i].resize(N); // 4 Spalten
  }
  while (input >> text)
  {
    if(x < 4){
      matrix[x][y] = hex_to_bitset(text);
      x++;
    }else{
      x = 0;
      y++;
      matrix[x][y] = hex_to_bitset(text);
      x++;
    }
  }

  return matrix;
}

//converts the ifstream key to a string vector with each key being 
vector<string> to_vecstring(ifstream &roundkey){
  vector<string> output;
  string line;
  while(!roundkey.eof()){
    getline(roundkey,line);
    output.push_back(line);
  }
  return output;
}

// converts the ifstream subbytes to vector of vector of strings
vector<vector<string>> to_bytes(ifstream &subbytes){
  vector<vector<string>> output;
  vector<string> substrings;
  string line;
  while(!subbytes.eof()){
    getline(subbytes,line);
    stringstream iss(line);
    do{
      string subs;
      iss >> subs;
      substrings.push_back(subs);
    }while(iss);
    output.push_back(substrings);
    substrings.clear();
  }

  return output;
}

// handles input and performs AES
vector<vector<bitset<8>>> init(ifstream &input, ifstream &roundkey, ifstream &subbytes){
  vector<vector<bitset<8>>> matrix = to_block(input);
  vector<string> keys = to_vecstring(roundkey);
  vector<vector<string>> bytes = to_bytes(subbytes);
  
  matrix = add_roundkey(matrix, keys[0]);
  for(size_t i = 1; i < 10; i++){
    matrix = sub(matrix, bytes);
    matrix = shiftrows(matrix);
    matrix = mixcolumns(matrix);
    matrix = add_roundkey(matrix, keys[i]);
  }
  matrix = sub(matrix, bytes);
  matrix = shiftrows(matrix);
  matrix = add_roundkey(matrix, keys[10]);

  return matrix;
}
// handles input and performs dekrypt of the AES
vector<vector<bitset<8>>> inv_init(ifstream &input, ifstream &roundkey, ifstream &subbytes){
  vector<vector<bitset<8>>> matrix = to_block(input);
  vector<string> keys = to_vecstring(roundkey);
  vector<vector<string>> bytes = to_bytes(subbytes);
  
  matrix = add_roundkey(matrix, keys[10]);
  for(size_t i = 9; i > 0; i--){
    matrix = sub(matrix, bytes);
    matrix = invshiftrows(matrix);
    matrix = add_roundkey(matrix, keys[i]);
    matrix = inv_mixcolumns(matrix);
  }
  matrix = sub(matrix, bytes);
  matrix = invshiftrows(matrix);
  matrix = add_roundkey(matrix, keys[0]);

  return matrix;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream> 
using namespace std;
const int N = 4;

/*
TODO:
1. Betriebsmodi einbauen
1.1 ECB 

- bessere Lösung für sbox input überlegen maybe irgendwas mit immer 

1.2 CBC
- 31.01
1.3 OFB
- 31.01
1.4 CTR
- 31.01

*/

vector<vector<int>> encrypt = {{2,3,1,1}, {1,2,3,1},{1,1,2,3},{3,1,1,2}};
vector<vector<int>> decrypt = {{14,11,13,9}, {9,14,11,13},{13,9,14,11},{11,13,9,14}};
vector<bitset<8>> rconTable = {bitset<8>("00000001"),bitset<8>("00000010"),bitset<8>("00000100"),bitset<8>("00001000"),
                              bitset<8>("00010000"),bitset<8>("00100000"),bitset<8>("01000000"),bitset<8>("10000000"),
                              bitset<8>("00011011"),bitset<8>("00110110")};
vector<vector<string>> sbox;
void print_matrix_hex(vector<vector<bitset<8>>> matrix){
  stringstream res;
  for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[i].size();j++){
			res << hex << uppercase << matrix[i][j].to_ulong();
      cout << res.str() << " ";
      res.str("");
    }
    cout << endl;
  }
}

void print_matrix(vector<vector<bitset<8>>> matrix){
    for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[i].size();j++){
			cout<<matrix[i][j]<<" ";
    }
		cout<<endl;
	}
}

string matrix_hex(vector<vector<bitset<8>>> matrix){
  stringstream res;
  string output, temp;
  for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[i].size();j++){
			res << hex << matrix[j][i].to_ulong();
      temp = res.str();
      if(temp.size() < 2){
        temp.insert(0, "0");
      }
      output.append(temp);
      output.append(" ");
      res.str("");
    }
  }
  output.pop_back();
  return output;
}

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

bitset<8> lookup(string hex){

  int temp[2];
  if(hex.size() == 2){
    for(size_t i = 0; i < 2; i++){
      if(hex[i] - '0' > 9){
        temp[i] = (hex[i] - 'a') + 10;
      }else{
        temp[i] = hex[i] - '0';
      }
    }
    return hex_to_bitset(sbox[temp[0]][temp[1]]);
  }else{
    if(hex[0] - '0' > 9){
      temp[0] = (hex[0] - 'a') + 10;
    }else{
      temp[0] = hex[0] - '0';
    }
    return hex_to_bitset(sbox[0][temp[0]]);
  }
}

vector<vector<bitset<8>>> sub(vector<vector<bitset<8>>> matrix){

  string subtring;
  stringstream res; 
  for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
      res.str("");
			res << hex  << matrix[i][j].to_ulong();
      matrix[i][j] = lookup(res.str());
    }
  }
  return matrix;
}

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

bitset<8> multi(bitset<8> input){
  bitset<8> b("00011011");
  bitset<8> output = input<<1;
  if(input[7]){
    return output ^= b; 
  }else{
    return output;
  }
}

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

bitset<8> mamul(vector<bitset<8>> column, vector<int> gal){
  bitset<8> a0 = add(column[0], gal[0]);
  bitset<8> a1 = add(column[1], gal[1]);
  bitset<8> a2 = add(column[2], gal[2]);
  bitset<8> a3 = add(column[3], gal[3]);
  return (a0 ^= a1 ^= a2 ^= a3);
}

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

vector<vector<bitset<8>>> to_block(string input){
  string text;
  stringstream res(input);
  size_t x = 0;
  size_t y = 0;
  vector<vector<bitset<8>>> matrix;
  matrix.resize(N); // 4 Zeilen
  for (int i = 0; i < N; ++i) {
    matrix[i].resize(N); // 4 Spalten
  }
  while (res >> text)
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

vector<string> to_vecstring(ifstream &roundkey){
  vector<string> output;
  string byte;
  string keyWord;
  size_t i = 0;
  while(roundkey >> byte){
    keyWord.append(byte);
    keyWord.append(" ");
    i++;
    if(i == 4){
      output.push_back(keyWord);
      keyWord.clear();
      i = 0;
    }
  }
  return output;
}

void to_bytes(ifstream &subbytes){
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
  sbox = output;
}

vector<vector<bitset<8>>> init(string input, vector<string> keys){
  vector<vector<bitset<8>>> matrix = to_block(input);
  
  matrix = add_roundkey(matrix, keys[0]);
  for(size_t i = 1; i < 10; i++){
    matrix = sub(matrix);
    matrix = shiftrows(matrix);
    matrix = mixcolumns(matrix);
    matrix = add_roundkey(matrix, keys[i]);
  }
  matrix = sub(matrix);
  matrix = shiftrows(matrix);
  matrix = add_roundkey(matrix, keys[10]);

  return matrix;
}

vector<vector<bitset<8>>> inv_init(string input, vector<string> keys ){
  vector<vector<bitset<8>>> matrix = to_block(input);
  matrix = add_roundkey(matrix, keys[10]);
  for(size_t i = 9; i > 0; i--){
    matrix = sub(matrix);
    matrix = invshiftrows(matrix);
    matrix = add_roundkey(matrix, keys[i]);
    matrix = inv_mixcolumns(matrix);
  }
  matrix = sub(matrix);
  matrix = invshiftrows(matrix);
  matrix = add_roundkey(matrix, keys[0]);

  return matrix;
}

//XOR 2 Hex 
string XOR(string a, string b){
  if(a.size() != b.size()){
    cerr << "Wrong Size in XOR, string ;" << endl;
    cerr << "a: " << a << " size: " << a.size() << "|| b: "<< b << " size: " << b.size() << endl;
    return a;
  }

  stringstream a_iss(a), b_iss(b), res;
  bitset<8> temp;
  string output, subs, subs2;;
  while (a_iss >> subs &&  b_iss >> subs2){
    temp = hex_to_bitset(subs) ^ hex_to_bitset(subs2);
    res << hex << temp.to_ulong();
    string tmp = res.str();
    if(tmp.size() < 2){
      tmp.insert(0,"0");
      output.append(tmp + " ");
    }else{
      output.append(tmp + " ");
    }
    res.str("");
  }
  output.pop_back();
  return output;
}

vector<bitset<8>> XOR(vector<bitset<8>> one, vector<bitset<8>> two){
  if(one.size() == two.size()){
    for(size_t i = 0; i < one.size();i++){
      one[i] ^= two[i];
    }
  }else{
    cerr << "Wrong Size in XOR, bitset" << endl;
  }
  return one;
}

vector<bitset<8>> rCon (int i){
  vector<bitset<8>> output;
  output.push_back(rconTable[i]);
  output.push_back(bitset<8>("00000000"));
  output.push_back(bitset<8>("00000000"));
  output.push_back(bitset<8>("00000000"));
  return output;
}

vector<bitset<8>> SubWord(vector<bitset<8>> rotWord){
  vector<bitset<8>> output;
  stringstream res;
  for(auto const &i: rotWord){
    res << hex << i.to_ulong();
    output.push_back(lookup(res.str()));
    res.str("");
  }
  return output;
}

vector<bitset<8>> RotWord(string w){
  vector<bitset<8>> temp, output;
  stringstream res(w);
  do{
    string subs;
    res >> subs;
    temp.push_back(hex_to_bitset(subs));
  }while(res);
  output.push_back(temp[1]);
  output.push_back(temp[2]);
  output.push_back(temp[3]);
  output.push_back(temp[0]);

  return output;
}
string keyGenmod (string W, string subword, int i){
  vector<bitset<8>> w, rconSet, temp, output;
  string re,subs;
  stringstream res(W);
  while(res >> subs){
    w.push_back(hex_to_bitset(subs));
  }
  temp= XOR(w, rCon((i/4) - 1));
  output = XOR(temp, SubWord(RotWord(subword)));
  stringstream iss;
  for(const auto &i : output){
    iss << hex << i.to_ulong();
    string tmp = iss.str();
    if(tmp.size() < 2){
      tmp.insert(0,"0");
      re.append(tmp + " ");
    }else{
      re.append(tmp + " ");
    }
    iss.str("");
  }
  re.pop_back();
  return re;
}

vector<string> keyGen(vector<string> ogKey){
  vector<string> keys;
  string W[44];
  string key;
  for(size_t i = 0; i < ogKey.size();i++){
    W[i] = ogKey[i];
    W[i].pop_back();
    key.append(ogKey[i]);
  }
  key.pop_back(); // remove last whitespace
  keys.push_back(key);
  key.clear();
  for(size_t i = 4; i < 44; i++){
    if(i % 4 == 0){
      W[i] = keyGenmod(W[i-4],W[i-1],i);
    }else{
      W[i] = XOR(W[i-4], W[i-1]);
    }
  }
  for(size_t i = 0; i < 40; i++){
    if(i % 4 == 0 && i != 0){
      key.pop_back();
      keys.push_back(key);
      key.clear();
    }
    key.append(W[i + 4]);
    key.append(" ");
  }
  key.pop_back();
  keys.push_back(key);
  return keys;
}

string pad(string block, int counter, int length){
  for(int i = counter; i < length; i++){
    block.append("00");
    block.append(" ");
  }
  block.pop_back();
  return block;
}

string IV(string block, string iv){
  string subs1, subs2, output;
  stringstream res1(block), res2(iv);
  while (res1 >> subs1 &&  res2 >> subs2)
  {
    output.append(XOR(subs1, subs2));
    output.append(" ");
  }
  output.pop_back();
  return output;
}

void ECB(ifstream &input, ifstream &key, ifstream &sbox){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key));
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block;
  size_t counter = 0;
  vector<vector<bitset<8>>> matrix;

  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      matrix = init(block,keys);
      print_matrix_hex(matrix);
      block.clear();
      counter = 0;
    }
  }
  if( counter > 0){
    matrix = init(pad(block, counter, keyLength),keys);
    print_matrix(matrix);
    block.clear();
  }
}

void CBC(ifstream &input, ifstream &key, ifstream &sbox, string iv){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key));
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block;
  size_t counter = 0;
  vector<vector<bitset<8>>> matrix;

  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      matrix = init(IV(block, iv),keys);
      print_matrix_hex(matrix);
      iv = matrix_hex(matrix);
      block.clear();
      counter = 0;
    }
  }
  if(counter > 0){
    matrix = init(IV(pad(block, counter, keyLength),iv),keys);
    print_matrix(matrix);
    block.clear();
  }
}

void OFB(ifstream &input, ifstream &key, ifstream &sbox, string iv){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key));
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block;
  size_t counter = 0;
  vector<vector<bitset<8>>> matrix;

  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      matrix = init(iv,keys);
      iv = matrix_hex(matrix);
      cout << XOR(block, iv);
      block.clear();
      counter = 0;
    }
  }
  if(counter > 0){
    matrix = init(iv,keys);
    cout << XOR(block, iv);
    block.clear();
  }
}

string incCounter(size_t x, size_t keyLength){
  stringstream res;
  res << hex << x;

  string output, temp;
  if(res.str().size() % 2 != 0){
    temp.append("0");
    temp.append(res.str());
  }else{
    temp.append(res.str());
  }
  for(size_t i = 0; i < temp.size();i++){
    if(i % 2 == 0 && i != 0){
      output.append(" ");
    }
    output += temp[i];
  }
  output.append(" ");
  for(size_t i = 0; i <= keyLength-temp.size();i++){
    output.append("00");
    output.append(" ");
  }
  output.pop_back();
  return output;
}

void CTR(ifstream &input, ifstream &key, ifstream &sbox, string iv){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key));
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block;
  string stringCounter("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00");
  size_t counter = 0, cc = 0;
  vector<vector<bitset<8>>> matrix;

  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      stringCounter = XOR(iv, stringCounter);
      matrix = init(stringCounter,keys);
      cc++;
      stringCounter = incCounter(cc, keyLength);
      cout << XOR(block, matrix_hex(matrix)) << endl;
      block.clear();
      counter = 0;
    }
  }
  if(counter > 0){
    stringCounter = XOR(iv, stringCounter);
    matrix = init(stringCounter,keys);
    cout << XOR(pad(block, counter, keyLength), matrix_hex(matrix));
    block.clear();
  }
}

void De_EBC (ifstream &input, ifstream &key, ifstream &sbox, ifstream &invsbox){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key)); // normal boxes to generate key
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block;
  size_t counter = 0;
  vector<vector<bitset<8>>> matrix;
  to_bytes(invsbox); // now invers boxes for block 
  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      matrix = inv_init(block,keys);
      print_matrix_hex(matrix);
      block.clear();
      counter = 0;
    }
  }
  if( counter > 0){
    init(pad(block, counter, keyLength), keys);
    matrix = init(block,keys);
    print_matrix(matrix);
    block.clear();
  }
}

void De_CBC(ifstream &input, ifstream &key, ifstream &sbox, ifstream &invsbox, string iv){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key)); // benutzt andere boxen 
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block, new_iv;
  size_t counter = 0;
  vector<vector<bitset<8>>> matrix;
  to_bytes(invsbox);
  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      new_iv = block;
      matrix = inv_init(block,keys);
      cout << XOR(matrix_hex(matrix), iv); //output
      iv = new_iv;
      block.clear();
      counter = 0;
    }
  }
  if( counter > 0){
    matrix = init(pad(block, counter, keyLength), keys);
    cout << XOR(matrix_hex(matrix), iv); //output
    block.clear();
  }
}

void De_OFB(ifstream &input, ifstream &key, ifstream &sbox, ifstream &invsbox, string iv){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key)); // benutzt andere boxen 
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block, cypher, new_iv;
  size_t counter = 0;
  vector<vector<bitset<8>>> matrix;
  to_bytes(invsbox);
  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      matrix = inv_init(iv,keys);
      cypher = matrix_hex(matrix);
      cout << XOR(cypher, iv); //output
      iv = cypher;
      block.clear();
      counter = 0;
    }
  }
  if( counter > 0){
    matrix = init(iv, keys);
    cypher = pad(block, counter, keyLength);
    cout << XOR(cypher, matrix_hex(matrix)); //output
    block.clear();
  }
}
void De_CTR(ifstream &input, ifstream &key, ifstream &sbox, ifstream &invsbox, string iv){
  to_bytes(sbox);
  vector<string> keys = keyGen(to_vecstring(key));
  size_t keyLength = (keys[0].length() - 15 )/2; // 15 is exclude whitespaces and a hex got 2 char 

  string word, block;
  string stringCounter("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00");
  size_t counter = 0, cc = 0;
  vector<vector<bitset<8>>> matrix;
  to_bytes(invsbox);
  while(input >> word){ // input is data as hex 
    block.append(word);
    block.append(" ");
    counter++;
    if(counter == keyLength){
      block.pop_back();
      stringCounter = XOR(iv, stringCounter);
      matrix = init(stringCounter,keys);
      cc++;
      stringCounter = incCounter(cc, keyLength);
      cout << XOR(block, matrix_hex(matrix));
      block.clear();
      counter = 0;
    }
  }
  if(counter > 0){
    stringCounter = XOR(iv, stringCounter);
    matrix = init(stringCounter,keys);
    cout << XOR(pad(block, counter, keyLength), matrix_hex(matrix));
    block.clear();
  }
}
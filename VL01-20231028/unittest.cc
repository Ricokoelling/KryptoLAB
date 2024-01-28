#include "kryp.h"

#include <cassert>
#include <cstdlib>

using namespace std;

size_t counter = 0;
main(){
  //Test ADD
  cout << "Running all test" << endl;
  cout << "Run test: " << counter++ << endl;
  assert(add('A',"0") == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(add('A', "26") == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(add('A', "10") == 'K');
  cout << "Run test: " << counter++ << endl;
  assert(add('Z', "1") == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(add('Z', "15") == 'O');
  cout << "Run test: " << counter++ << endl;
  assert(add(',', "15") == ',');
  cout << "Run test: " << counter++ << endl;
  assert(add(' ', "12") == ' ');
  cout << "Run test: " << counter++ << endl;
  assert(add('.', "13") == '.');
  cout << "Run test: " << counter++ << endl;
  assert(add('/', "18") == '/');
  cout << "Run test: " << counter++ << endl;
  assert(add('"', "5") == '"');

  // Test add_krypt init
  ifstream text;
  ofstream k_text;
  if(!text || !k_text){
    return 0;
  }
  text.open ("Klartext_1.txt");
  k_text.open("Output.txt");
  const string key = "7";
  add_krypt(text, key ,k_text);
  k_text.close();
  text.close();

  string line_input;
  string line_input_eq;
  ifstream test_input;
  ifstream test_input_eq;
  test_input.open ("Output.txt");
  test_input_eq.open("Kryptotext_1_Key_7.txt");

  // Test add_krypt
  cout << "Run test: " << counter++ << endl;
  while(getline(test_input, line_input) && getline(test_input_eq, line_input_eq)){
    assert(line_input.size() == line_input_eq.size());
    for(size_t i = 0; i < line_input.size(); i++){
      assert(line_input[i] == line_input_eq[i]);
    }
  }

  //Test sub 
  cout << "Run test: " << counter++ << endl;
  assert(sub('A',"0") == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(sub('A', "26") == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(sub('A', "10") == 'Q');
  cout << "Run test: " << counter++ << endl;
  assert(sub('Z', "1") == 'Y');
  cout << "Run test: " << counter++ << endl;
  assert(sub('Z', "15") == 'K');
  cout << "Run test: " << counter++ << endl;
  assert(sub(',', "15") == ',');
  cout << "Run test: " << counter++ << endl;
  assert(sub(' ', "12") == ' ');
  cout << "Run test: " << counter++ << endl;
  assert(sub('.', "13") == '.');
  cout << "Run test: " << counter++ << endl;
  assert(sub('/', "18") == '/');
  cout << "Run test: " << counter++ << endl;
  assert(sub('"', "5") == '"');


  //Test sub_krypt
  ifstream de_text;
  ofstream de_k_text;
  if(!de_text || !de_k_text){
    return 0;
  }
  de_text.open ("sampleEncrypted.txt");
  de_k_text.open("new_klartext.txt");
  const string de_key = "7";
  sub_krypt(de_text, de_key ,de_k_text);
  de_k_text.close();
  de_text.close();

  string de_line_input;
  string de_line_input_eq;
  ifstream de_test_input;
  ifstream de_test_input_eq;
  de_test_input.open ("new_klartext.txt");
  de_test_input_eq.open("og_text.txt ");

  // Test add_krypt
  cout << "Run test: " << counter++ << endl;
  while(getline(de_test_input, de_line_input) && getline(de_test_input_eq, de_line_input_eq)){
    assert(de_line_input.size() == de_line_input_eq.size());
    for(size_t i = 0; i < de_line_input.size(); i++){
      assert(de_line_input[i] == de_line_input_eq[i]);
    }
  }
  de_test_input.close();
  de_test_input_eq.close();
  cout << "All test passed!" << endl;
}
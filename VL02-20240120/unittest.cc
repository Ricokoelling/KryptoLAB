#include "krypt.h"

#include <cassert>
#include <cstdlib>

using namespace std;

size_t counter = 0;
main()
{
  cout << "Running all test" << endl;
  cout << "Run test: " << counter++ << endl;
  assert(add('A', 'A') == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(add('A', 'Z') == 'Z');
  cout << "Run test: " << counter++ << endl;
  assert(add('A', 'K') == 'K');
  cout << "Run test: " << counter++ << endl;
  assert(add('Z', 'A') == 'Z');
  cout << "Run test: " << counter++ << endl;
  assert(add('Z', 'P') == 'O');

  //Test vigenere_krypt
  ifstream text;
  ofstream en_text;
  if(!text || !en_text){
    return 0;
  }
  text.open ("Klartext_1.txt");
  en_text.open("Output.txt");
  const string key = "TAG";
  vigenere_krypt(text, key, en_text);
  en_text.close();
  text.close();

  string line_input;
  string line_input_eq;
  ifstream test_input;
  ifstream test_input_eq;
  test_input.open ("Output.txt");
  test_input_eq.open("Kryptotext_TAG.txt");

  // Test vigenere_krypt
  cout << "Run test: " << counter++ << endl;
  while(getline(test_input, line_input) && getline(test_input_eq, line_input_eq)){
    assert(line_input.size() == line_input_eq.size());
    for(size_t i = 0; i < line_input.size(); i++){
      assert(line_input[i] == line_input_eq[i]);
    }
  }

  //Test sub
  cout << "Run test: " << counter++ << endl;
  assert(sub('A','A') == 'A');
  cout << "Run test: " << counter++ << endl;
  assert(sub('A', 'Z') == 'B');
  cout << "Run test: " << counter++ << endl;
  assert(sub('A', 'K') == 'Q');
  cout << "Run test: " << counter++ << endl;
  assert(sub('Z', 'B') == 'Y');
  cout << "Run test: " << counter++ << endl;
  assert(sub('Z', 'P') == 'K');


  //Test vigenere_enkrypt
  ifstream de_text;
  ofstream de_k_text;
  if(!de_text || !de_k_text){
    return 0;
  }
  de_text.open ("Kryptotext_TAG.txt");
  de_k_text.open("new_klartext.txt");
  const string de_key = "TAG";
  vigenere_enkrypt(de_text,key, de_k_text);
  de_k_text.close();
  de_text.close();

  string de_line_input;
  string de_line_input_eq;
  ifstream de_test_input;
  ifstream de_test_input_eq;
  de_test_input.open ("new_klartext.txt");
  de_test_input_eq.open("Klartext_1.txt ");

  // Test vigenere_enkrypt
  cout << "Run test: " << counter++ << endl;
  while(getline(de_test_input, de_line_input) && getline(de_test_input_eq, de_line_input_eq)){
    assert(de_line_input.size() == de_line_input_eq.size());
    for(size_t i = 0; i < de_line_input.size(); i++){
      assert(de_line_input[i] == de_line_input_eq[i]);
    }
  }
  de_test_input.close();
  de_test_input_eq.close();
  cout << "All tests passed!" << endl;
}
#include <iostream>
#include <vector>

#include "sort.hpp"

using namespace std;

int main(){
  vector<vector<char>> data {{'1', 'H', 'P'}, {'A', 'Y', '6'}, {'F', '2', 'K'}, {'7', '8', 'L'}, {'R', 'I', 'N'}, {'X', 'U', '9'}};

  Sort::quick_sort(data, 1, 0, data.size()-1);
  Sort::print_vector_2d(data);

  // int a = 1;
  // int& c = a;
  // int *b = &a;
  // int d = a;

  // cout << "value of b (address): " << b << endl;
  // cout << "value of *b: " << *b << endl;
  // cout << "value of c: " << c << endl;
  // cout << "value of d: " << d << endl;

  // cout << "-----------------------------------------"  << endl;

  // c = 2;

  // cout << "value of b (address): " << b << endl;
  // cout << "value of *b: " << *b << endl;
  // cout << "value of c: " << c << endl;
  // cout << "value of d: " << d << endl;
}

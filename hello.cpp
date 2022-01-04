#include <iostream>
#include <vector>
#include "sort-vector.hpp"

using namespace std;

int main(){
  // vector<vector<char> > data { {'1', 'H', 'P'}, {'A', 'Y', '6'}, {'F', '2', 'K'}, {'7', '8', 'L'}, {'R', 'I', 'N'}, {'X', 'U', '9'}};

  vector<int> vectorData {7, 2, 6, 8, 1, 3, 5, 4};

  SortVector sort;
  sort.quickSort(vectorData, 0, 7);
  sort.printVector(vectorData);

  int data[] = {7, 2, 6, 8, 1, 3, 5, 4};

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

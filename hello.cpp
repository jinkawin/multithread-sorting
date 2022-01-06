#include <iostream>
#include <vector>

#include "sort.hpp"

using namespace std;

#include "context.hpp"
#include "taskmanager.hpp"

int main(){
  vector<vector<char>> data {{'1', 'H', 'P'}, {'A', 'Y', '6'}, {'F', '2', 'K'}, {'7', '8', 'L'}, {'R', 'I', 'N'}, {'X', 'U', '9'}};
  vector<int> buckets_index;

  BucketContext context = {
    &data,
    &buckets_index,
    3, // total threads
    2 // sorting column
  };

  TaskManager::swapBucket(&context);

  Sort::printVector2d(data);
  Sort::printVector(buckets_index);

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

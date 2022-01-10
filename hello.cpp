#include <iostream>
#include <vector>

#include "context.hpp"
#include "taskmanager.hpp"
#include "sort.hpp"
#include "util.hpp"

using namespace std;

int main(){
  vector<vector<char>> data {{'a', 's', 'c'}, {'6', 'h', 'p'}, {'f', '3', 'x'}, {'n', 'r', '1'}, {'u', '9', 'j'}, {'t', 'i', '7'}};
  vector<int> buckets_index;

  BucketContext context = {
    &data,
    &buckets_index,
    3, // total threads
    2 // sorting column
  };

  TaskManager::swapBucket(&context);

  Util::printVector2d(data);
  Util::printVector(buckets_index);

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

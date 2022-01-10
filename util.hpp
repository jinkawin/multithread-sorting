#include <string>
#include <iostream>

using namespace std;

#ifndef UTIL_HPP
#define UTIL_HPP

class Util {
public:

  static void printVector(vector<int> data){
    for (const auto& elem : data) {
      cout << elem <<  ", ";
    }
    cout << endl;
  }

  static void printVector2d(vector<vector<char>> data) {
    for (const auto& row : data) {
      for (const auto& elem : row) {
        cout << elem <<  ", ";
      }
      cout << endl;
    }
  }
};

#endif
#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <iostream>

using namespace std;

class Util {
public:
  template <typename T>

  static void printVector(vector<T> data){
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
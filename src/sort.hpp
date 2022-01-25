#ifndef SORT_HPP
#define SORT_HPP

#include <string>
#include <iostream>

#include "config.hpp"

using namespace std;

class Sort {
public:
  static void quickSort(vector<vector<char>> &data, int64_t column, int64_t low, int64_t high) {
    if(low < 0 || high > Config::ALLOC_ROW_SIZE) return;

    if (low < high){
      int64_t mid = partition(data, column, low, high);

      quickSort(data, column, low, mid - 1);
      quickSort(data, column, mid + 1, high);
    }
  }

private:
  static int64_t partition(vector<vector<char>> &data, int64_t column, int64_t low, int64_t high) {
    const int64_t pivot = data[high][column];
    int64_t i = (low - 1);

    for (auto j = low; j <= high - 1; j++){
      if (data[j][column] <= pivot){
        swap(data[++i], data[j]);
      }
    }
    swap(data[++i], data[high]);

    return i;
  }
};

#endif
#ifndef COLUMN_SORT_HPP
#define COLUMN_SORT_HPP

#include <string>
#include <iostream>

#include "util.hpp"
#include "config.hpp"

using namespace std;

class ColumnSort {
public:
  inline static int column = 0;

public:
  static void columnSort(vector<vector<char>>& data, uint64_t start_idx, uint64_t last_idx) {
    const uint64_t alloc_size = last_idx - start_idx + 1;
    vector<vector<char>> temp(alloc_size, vector<char>(Config::ALLOC_COL_SIZE));
    temp.assign(data.begin() + start_idx, data.begin() + last_idx + 1);

    sort(temp.begin(), temp.end(), ColumnSort::compareColumn);

    for(auto i=0; i<temp.size(); i++) {
      data[start_idx + i] = temp[i];
    }
  }

private:
  static bool compareColumn(const vector<char>& v1, const vector<char>& v2) {
    return v1[ColumnSort::column] < v2[ColumnSort::column];
  }
};

#endif
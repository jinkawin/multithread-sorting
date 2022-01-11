#ifndef SORT_HPP
#define SORT_HPP

#include <string>
#include <iostream>

using namespace std;

class Sort {
public:

  static void quickSort(vector<vector<char>> &data, int column, int low, int high) {
    if (low < high){
      int mid = partition(data, column, low, high);

      quickSort(data, column, low, mid - 1);
      quickSort(data, column, mid + 1, high);
    }
  }

private:
  static int partition(vector<vector<char>> &data, int column, int low, int high) {
    const int pivot = data[high][column];
    int i = (low - 1);

    for (auto j = low; j <= high - 1; j++){
      if (data[j][column] <= pivot){
        swap(data[++i], data[j]);
      }
    }
    swap(data[++i], data[high]);

    return i;
  }

  static vector<char> getColumn(vector<vector<char>> &data, int column){
    vector<char> result;

    for (const auto& row : data) {
      result.push_back(row[column]);
    }

    return result;
  }
};

#endif
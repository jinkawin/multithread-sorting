#include <string>
#include <iostream>

using namespace std;

#ifndef SORT_HPP
#define SORT_HPP

class Sort {
public:

  static void quickSort(vector<vector<char>> &data, int column, int low, int high) {
    if (low < high){
      int mid = partition(data, column, low, high);

      quickSort(data, column, low, mid - 1);
      quickSort(data, column, mid + 1, high);
    }
  }

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

private:
  static int partition(vector<vector<char>> &data, int column, int low, int high) {
    int pivot = data[high][column];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++){
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
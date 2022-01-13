#ifndef SORT_HPP
#define SORT_HPP

#include <string>
#include <iostream>

using namespace std;

class Sort {
private:
  vector<vector<char>> &data;

public:
  Sort(vector<vector<char>> &arr)
    :data(arr) {}

  void quickSort(int column, int low, int high) {
    if (low < high){
      int mid = partition(column, low, high);

      quickSort(column, low, mid - 1);
      quickSort(column, mid + 1, high);
    }
  }

private:
  int partition(int column, int low, int high) {
    const int pivot = this->data[high][column];
    int i = (low - 1);

    for (auto j = low; j <= high - 1; j++){
      if (this->data[j][column] <= pivot){
        swap(this->data[++i], this->data[j]);
      }
    }
    swap(this->data[++i], this->data[high]);

    return i;
  }
};

#endif
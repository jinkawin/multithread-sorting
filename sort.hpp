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

  static int getMax(vector<int> &data) {
    int max = data[0];
    for (int i = 1; i < data.size(); i++)
      if (data[i] > max)
        max = data[i];
    return max;
  }

  // Using counting sort to sort the elements in the basis of significant places
  static void countingSort(vector<int> &data, int place) {
    const int max = 10;
    const int size = data.size();
    int output[size];
    int count[max];

    for (int i = 0; i < max; ++i)
      count[i] = 0;

    // Calculate count of elements
    for (int i = 0; i < size; i++)
      count[(data[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < max; i++)
      count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--) {
      output[count[(data[i] / place) % 10] - 1] = data[i];
      count[(data[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
      data[i] = output[i];
  }

  // Main function to implement radix sort
  static void radixsort(vector<int> &data) {
    // Get maximum element
    int max = getMax(data);

    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10){
      cout << "place: " << place << endl;
      countingSort(data, place);
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
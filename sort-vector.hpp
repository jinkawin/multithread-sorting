#include <string>
#include <iostream>

using namespace std;

class SortVector {
public:

  void quickSort(vector<vector<char>> &data, int column, int low, int high) {
    if (low < high){
      int mid = this->partition(data, column, low, high);

      quickSort(data, column, low, mid - 1);
      quickSort(data, column, mid + 1, high);
    }
  }

  void printVector(vector<char> data){
    for (const auto& elem : data) {
      cout << elem <<  ", ";
    }
    cout << endl;
  }

  void printVector2D(vector<vector<char>> data) {
    for (const auto& row : data) {
      for (const auto& elem : row) {
        cout << elem <<  ", ";
      }
      cout << endl;
    }
  }

  vector<char> getColumn(vector<vector<char>> data, int column){
    vector<char> result;

    for (const auto& row : data) {
      result.push_back(row[column]);
    }

    return result;
  }

private:
  int partition(vector<vector<char>> &data, int column, int low, int high) {
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
};

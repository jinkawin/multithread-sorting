#include <string>
#include <iostream>

using namespace std;

class SortVector {
public:

  void quickSort(vector<int> &data, int low, int high) {
    if (low < high){
      int mid = this->partition(data, low, high);

      quickSort(data, low, mid - 1);
      quickSort(data, mid + 1, high);
    }
  }

  void printVector(vector<int> data) {
    for (const auto& elem : data) {
      cout << elem << ", ";
    }

    cout << endl;
  }

private:
  int partition(vector<int> &data, int low, int high) {
    int pivot = data[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++){
      if (data[j] <= pivot){
        swap(&data[++i], &data[j]);
      }
    }
    swap(&data[++i], &data[high]);
    return i;
  }

  void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
  }
};

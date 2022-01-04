#include <string>
#include <iostream>

using namespace std;

class Sort {
public:

  void quickSort(int *arr, int low, int high){
    if (low < high){
      int mid = this->partition(arr, low, high);

      quickSort(arr, low, mid - 1);
      quickSort(arr, mid + 1, high);
    }
  }

  void printArray(int arr[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
  }

private:
  int partition(int *arr, int low, int high){
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++){
      if (arr[j] <= pivot){
        swap(&arr[++i], &arr[j]);
      }
    }
    swap(&arr[++i], &arr[high]);
    return i;
  }

  void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
  }
};

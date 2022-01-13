#include <pthread.h>
#include <thread>
#include <vector>

#include "filemanager.hpp"
#include "taskmanager.hpp"
#include "context.hpp"
#include "util.hpp"

using namespace std;

int main() {
  const unsigned int START_INDEX = 4; // start after "USR:"
  const unsigned int ALLOC_ROW_SIZE = 10; // Reserve extra space for preventing "Segmentation fault: 11"
  const unsigned int ALLOC_COL_SIZE = 10; // Reserve extra space for preventing "Segmentation fault: 11"

  // Thread initialisation
  volatile uint8_t running_threads = 0;
  unsigned int total_threads = thread::hardware_concurrency();
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

  // Data Initialisation
  vector<int> buckets_index;
  vector<vector<char>> data(ALLOC_ROW_SIZE, vector<char>(ALLOC_COL_SIZE));
  FileManager::read("data/reversed_users_10k.csv", data);

  // Find last position of the first column (by finging the first comma)
  int last_index;
  for(double i = 0; i < data[0].size(); i++) {
    if(data[0][i] == ',') {
      last_index = i-1;
      break;
    }
  }

  // A number of cores cannot exceed a number of data's row
  total_threads = (total_threads < data.size()) ? total_threads : data.size();

  // Initial Bucket index
  BucketContext bucketContext = {
    &data,
    &buckets_index,
    total_threads,
    START_INDEX
  };
  TaskManager::swapBucket(&bucketContext);

  // Sorting
  for(int i = last_index; i >= START_INDEX; i--) {
    SortContext sortContext = {
      &data,
      &buckets_index,
      running_mutex,
      running_threads,
      total_threads,
      i
    };
    TaskManager::localSort(&sortContext);

    BucketContext bucketContext = {
      &data,
      &buckets_index,
      total_threads,
      i
    };
    TaskManager::swapBucket(&bucketContext);
  }

  // Post-process
  SortContext sortContext = {
    &data,
    &buckets_index,
    running_mutex,
    running_threads,
    total_threads,
    START_INDEX
  };
  TaskManager::localSort(&sortContext);

  FileManager::write("out.txt", data);

  pthread_exit(NULL);

  return 0;
}

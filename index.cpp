#include <pthread.h>
#include <thread>
#include <vector>

#include "filemanager.hpp"
#include "taskmanager.hpp"
#include "context.hpp"
#include "util.hpp"

using namespace std;

int main() {
  const int START_INDEX = 4; // start after "USR:"

  // Thread initialisation
  volatile uint8_t running_threads = 0;
  unsigned int total_threads = thread::hardware_concurrency();
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

  // Data Initialisation
  vector<int> buckets_index;
  vector<vector<char>> data;
  FileManager::read("test1.txt", data);

  // Find last position of the first column (by finging the first comma)
  int last_index;
  for(int i = 0; i < data[0].size(); i++) {
    if(data[0][i] == ',') {
      last_index = i;
      break;
    }
  }

  // A number of cores cannot exceed a number of data's row
  total_threads = (total_threads < data.size()) ? total_threads : data.size();

  // Initial Bucket index
  uint64_t bucket_size = data.size() / total_threads;
  for(uint64_t i = bucket_size-1; i < data.size(); i = i+bucket_size) {
    buckets_index.push_back(i);
  }

  // Sorting
  unsigned int sorting_column_size = last_index - START_INDEX;
  for(int i = sorting_column_size; i >= START_INDEX; i--) {
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
    0
  };
  TaskManager::localSort(&sortContext);

  FileManager::write("out.txt", data);
  cout << "finished" << endl;

  pthread_exit(NULL);

  return 0;
}
